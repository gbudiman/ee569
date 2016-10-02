//
//  GrainCategorizer.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/24/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "GrainCategorizer.hpp"
using namespace std;

GrainCategorizer::GrainCategorizer() {
  grains = vector<vector<Coordinate>>();
}

void GrainCategorizer::add(int r, int c) {
  Coordinate coord = Coordinate(r, c);
  bool group_found = false;
  
  for (int g = 0; g < grains.size(); g++) {
    vector<Coordinate> current_group = grains.at(g);
    
    for (int cg = 0; cg < current_group.size(); cg++) {
      Coordinate cc = current_group.at(cg);
      if (cc.has_connectivity(coord)) {
        group_found = true;
        //printf("%d <= %d, %d\n", g, r, c);
        grains.at(g).push_back(coord);
        break;
      }
    }
    
    if (group_found) {
      break;
    }
  }
  
  if (!group_found) {
    //printf("NEW GROUP: %d, %d\n", r, c);
    vector<Coordinate> new_group = vector<Coordinate>();
    new_group.push_back(coord);
    grains.push_back(new_group);
  }
}

int GrainCategorizer::count_groups() {
  int real_count = 0;
  
  for (int g = 0; g < grains.size(); g++) {
    int group_member_count = grains.at(g).size();
    
    real_count += group_member_count < GRAIN_BORDER_THRESHOLD ? 0 : 1;
  }
  
  return real_count;
}

void GrainCategorizer::debug_groups() {
//  int real_count = 0;
//  for (int g = 0; g < grains.size(); g++) {
//    vector<Coordinate> members = grains.at(g);
//    int bb_row_low = 0xFFFF;
//    int bb_row_high = 0;
//    int bb_col_low = 0xFFFF;
//    int bb_col_high = 0;
//    
//    if (members.size() < GRAIN_BORDER_THRESHOLD) {
//      continue;
//      //printf(" <<< GROUP %d (NOT COUNTED) >>>\n", g);
//    } else {
//      printf(" <<< GROUP %d >>>\n", ++real_count);
//    }
//    
//    for (int m = 0; m < members.size(); m++) {
//      int this_row = members.at(m).row;
//      int this_col = members.at(m).col;
//      if (this_row > bb_row_high) {
//        bb_row_high = this_row;
//      }
//      if (this_row < bb_row_low) {
//        bb_row_low = this_row;
//      }
//      if (this_col > bb_col_high) {
//        bb_col_high = this_col;
//      }
//      if (this_col < bb_col_low) {
//        bb_col_low = this_col;
//      }
//      
//      //printf("  (%d, %d)\n", this_row, this_col);
//    }
//    
//    printf(" (%d, %d) -> (%d, %d) === (%d, %d)\n", bb_col_low, bb_row_low, bb_col_high, bb_row_high, bb_col_high - bb_col_low, bb_row_high - bb_row_low);
//  }
  
//  float yellow_1 = (s1.chroma.r + s1.chroma.g * 3) / 4;
//  float blue_1 = s1.chroma.r + s1.chroma.g + s1.chroma.b * 0.3;
//  
//  float yellow_2 = (s2.chroma.r + s2.chroma.g * 3) / 4;
//  float blue_2 = s2.chroma.r + s2.chroma.g + s2.chroma.b * 0.3;
  
  for (int i = 0; i < grain_data.size(); i++) {
    SpatialData s = grain_data.at(i);
    if (s.area < 10) { continue; }
    printf("(%3d, %3d) | %4.0f | %3.1f x %3.1f | %.3f | (%3d,%3d,%3d) | %.2f | %.2f | %.4f // %.2d\n",
           s.spatial_center.col,
           s.spatial_center.row,
           s.area,
           s.length,
           s.width,
           s.width / s.length,
           s.chroma.r,
           s.chroma.g,
           s.chroma.b,
           (float) (s.chroma.r + s.chroma.g + s.chroma.b) / (255 * 3),
           (float) s.chroma.r / ((float) (s.chroma.g + s.chroma.b) / 2),
           ((float) (s.chroma.r + s.chroma.g * 3) / 4) / ((float) s.chroma.r + (float) s.chroma.g + (float) s.chroma.b * 0.3),
           pseudo_group(s.spatial_center.row, s.spatial_center.col));
  }
}

void GrainCategorizer::insert_area_data(Coordinate coord, float area) {
  SpatialData spd = SpatialData();
  spd.update_area(coord, area);
  grain_data.push_back(spd);
}

void GrainCategorizer::correlate_length(BoundingBox bb, float length) {
  for (int i = 0; i < grain_data.size(); i++) {
    if (bb.in_bounding_box(grain_data.at(i).spatial_center)) {
      grain_data.at(i).update_length(bb, length);
      grain_data.at(i).update_width();
    }
  }
}

void GrainCategorizer::correlate_chroma(Coordinate coord, RgbPixel p) {
  for (int i = 0; i < grain_data.size(); i++) {
    if (coord == grain_data.at(i).spatial_center) {
      grain_data.at(i).chroma = p;
    }
  }
}

int GrainCategorizer::pseudo_group(int r, int c) {
  int r_mult, c_add;
  
  if (r < 155) {
    r_mult = 0;
  } else if (r < 281) {
    r_mult = 1;
  } else if (r < 395) {
    r_mult = 2;
  } else {
    r_mult = 3;
  }
  
  if (c < 300) {
    c_add = 0;
  } else if (c < 520) {
    c_add = 1;
  } else {
    c_add = 2;
  }
  
  return r_mult * 3 + c_add;
}

struct scalar_area_comparator {
  inline bool operator() (const SpatialData& s1, const SpatialData& s2) {
    return (s1.area > s2.area);
  }
};

struct scalar_roundness_comparator {
  inline bool operator() (const SpatialData& s1, const SpatialData& s2) {
    return (s1.width / s1.length > s2.width / s2.length);
  }
};

struct scalar_lightness_comparator {
  inline bool operator() (const SpatialData& s1, const SpatialData& s2) {
    float f1 = (float) s1.chroma.r + (float) s1.chroma.g + (float) s1.chroma.b;
    float f2 = (float) s2.chroma.r + (float) s2.chroma.g + (float) s2.chroma.b;
    return (f1 > f2);
  }
};

struct scalar_location_comparator {
  inline bool operator() (const SpatialData& s1, const SpatialData& s2) {
    return (GrainCategorizer::pseudo_group(s1.spatial_center.row, s1.spatial_center.col) < GrainCategorizer::pseudo_group(s2.spatial_center.row, s2.spatial_center.col));
  }
};

struct scalar_yellow_chroma_comparator {
  inline bool operator() (const SpatialData& s1, const SpatialData& s2) {
    float yellow_1 = (float) (s1.chroma.r + (float) s1.chroma.g * 3.0) / 4.0;
    float blue_1 = s1.chroma.r + s1.chroma.g + (float) s1.chroma.b * 0.3;
    
    float yellow_2 = (float) (s2.chroma.r + (float) s2.chroma.g * 3.0) / 4.0;
    float blue_2 = s2.chroma.r + s2.chroma.g + (float) s2.chroma.b * 0.3;
    
    return (yellow_1 / blue_1 > yellow_2 / blue_2);
  }
};

struct scalar_red_chroma_comparator {
  inline bool operator() (const SpatialData& s1, const SpatialData& s2) {
    float red_1 = s1.chroma.r;
    float gb_1 = (s1.chroma.b + s1.chroma.g) / 2;
    
    float red_2 = s2.chroma.r;
    float gb_2 = (s2.chroma.b + s2.chroma.g) / 2;
    
    return (red_1 / gb_1 > red_2 / gb_2);
  }
};

void GrainCategorizer::cluster_group_by_area() {
  sort(grain_data.begin(), grain_data.end(), scalar_area_comparator());
}

void GrainCategorizer::cluster_group_by_roundness() {
  sort(grain_data.begin(), grain_data.end(), scalar_roundness_comparator());
}

void GrainCategorizer::cluster_group_by_lightness() {
  sort(grain_data.begin(), grain_data.end(), scalar_lightness_comparator());
}

void GrainCategorizer::cluster_group_by_location() {
  sort(grain_data.begin(), grain_data.end(), scalar_location_comparator());
}

void GrainCategorizer::cluster_group_by_yellow_chroma() {
  sort(grain_data.begin(), grain_data.end(), scalar_yellow_chroma_comparator());
}

void GrainCategorizer::cluster_group_by_red_chroma() {
  sort(grain_data.begin(), grain_data.end(), scalar_red_chroma_comparator());
}

void GrainCategorizer::compute_average_size() {
  vector<float> average_by_group = vector<float>(11);
  vector<float> roundness_by_group = vector<float>(11);
  
  for (int i = 0; i < grain_data.size(); i++) {
    if (grain_data.at(i).area < GRAIN_AREA_THRESHOLD) { continue; }
    
    average_by_group.at(pseudo_group(grain_data.at(i).spatial_center.row, grain_data.at(i).spatial_center.col)) += grain_data.at(i).area;
    roundness_by_group.at(pseudo_group(grain_data.at(i).spatial_center.row, grain_data.at(i).spatial_center.col)) += grain_data.at(i).width / grain_data.at(i).length;
  }
  
  for (int i = 0; i < average_by_group.size(); i++) {
    average_by_group.at(i) /= 5;
    roundness_by_group.at(i) /= 5;
  }
  
  for (int i = 0; i < average_by_group.size(); i++) {
    printf("%3d %.2f %.2f\n", i, average_by_group.at(i), roundness_by_group.at(i));
  }
}