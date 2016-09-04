//
//  PatchMap.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "PatchMap.hpp"
using namespace std;

PatchMap::PatchMap(int row, int col, int _dim_x, int _dim_y, int search_radius, int _patch_radius, vector<vector<RgbPixel>*>* data) {
  picture_data = data;
  //cells = new vector<PatchCell>();
  dim_x = _dim_x;
  dim_y = _dim_y;
  patch_radius = _patch_radius;
  float weight_cumulative = 0;
  vector<NlmWeight>* nlm_weights = new vector<NlmWeight>();
  
  vector<vector<RgbPixel>*>* base_patch = create_base_patch(row, col);
  
  for (int r = row - search_radius; r <= row + search_radius; r++) {
    if (r < 0 || r > dim_y - 1) {
      continue;
    }
    
    for (int c = col - search_radius; c <= col + search_radius; c++) {
      if (c < 0 || c > dim_x - 1) {
        continue;
      }
      
      if (c == col && r == row) {
        continue;
      }
      
      float dist_x = (float) (row - r);
      float dist_y = (float) (col - c);
      float dist = dist_x * dist_x + dist_y * dist_y;
      
      
      
//      
//      cout << "patch includes (" << r << ", " << c << ")" << "\n";
//      PatchCell *cell = new PatchCell(dist, &data->at(r)->at(c));
//      cells->push_back(*cell);
      vector<vector<RgbPixel>*>* comp_patch = create_base_patch(r, c);
      float difference = (float) compute_patch_difference(base_patch, comp_patch);
      float diff_squared_negated = - difference * difference;
      float r_side = diff_squared_negated / NLM_H_SQUARED;
      float weight = exp(r_side);
      weight_cumulative += weight;
      
      NlmWeight* nw = new NlmWeight(r, c, weight);
      nlm_weights->push_back(*nw);
      
      printf("(%d, %d) <> (%d, %d) diff: %.3f | dist: %.3f weight: %.3f\n", row, col, r, c, difference, dist, weight);
    }
  }
  
  printf("Cumulative weight = %.3f\n", weight_cumulative);
  
  float denoise_red = 0;
  float denoise_green = 0;
  float denoise_blue = 0;
  RgbPixel target_pixel = picture_data->at(row)->at(col);
  
  for (auto i = nlm_weights->begin(); i != nlm_weights->end(); ++i) {
    int irow = i->row;
    int icol = i->col;
    float weight = i->weight;
    RgbPixel original_pixel = picture_data->at(irow)->at(icol);
    
    denoise_red += (weight / weight_cumulative) * (float) original_pixel.r;
    denoise_green += (weight / weight_cumulative) * (float) original_pixel.g;
    denoise_blue += (weight / weight_cumulative) * (float) original_pixel.b;
  }
  
  printf("(%d %d %d) -> (%.0f %.0f %.0f)\n", target_pixel.r, target_pixel.g, target_pixel.b, denoise_red, denoise_green, denoise_blue);

  result = new RgbPixel((int) denoise_red, (int) denoise_green, (int) denoise_blue);
}

vector<vector<RgbPixel>*>* PatchMap::create_base_patch(int row, int col) {
  int pos_r, pos_c = 0;
  vector<vector<RgbPixel>*>* base_patch = new vector<vector<RgbPixel>*>();
  
  //printf("Creating patch centered around (%d, %d)\n", row, col);
  for (int r = row - patch_radius; r <= row + patch_radius; r++) {
    vector<RgbPixel>* row_data = new vector<RgbPixel>();
    
    if (r >= dim_y) {
      int y_limit = dim_y - 1;
      int overshoot = r - y_limit;
      pos_r = y_limit - overshoot;
    } else {
      pos_r = abs(r);
    }
    
    for (int c = col - patch_radius; c <= col + patch_radius; c++) {
      if (c >= dim_x) {
        int x_limit = dim_x - 1;
        int overshoot = c - x_limit;
        pos_c = x_limit - overshoot;
      } else {
        pos_c = abs(c);
      }
      
      row_data->push_back(picture_data->at(pos_r)->at(pos_c));
    }
    
    base_patch->push_back(row_data);
  }
  
  return base_patch;
}

int PatchMap::compute_patch_difference(vector<vector<RgbPixel>*>* a, vector<vector<RgbPixel>*>* b) {
  int difference = 0;
  for (int i = 0; i < patch_radius; i++) {
    for (int j = 0; j < patch_radius; j++) {
      int diff_r = a->at(i)->at(j).r - b->at(i)->at(j).r;
      int diff_g = a->at(i)->at(j).g - b->at(i)->at(j).g;
      int diff_b = a->at(i)->at(j).b - b->at(i)->at(j).b;
      
      int diff_color = diff_r * diff_r + diff_g * diff_g + diff_b * diff_b;
      difference += diff_color / 9;
    }
  }
  
  return difference;
}