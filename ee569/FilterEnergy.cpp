//
//  FilterEnergy.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/13/16.
//  Finalized on 10/31/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "FilterEnergy.hpp"
using namespace std;
using namespace cv;

FilterEnergy::FilterEnergy() {
  data = vector<vector<vector<float>>>();
}

void FilterEnergy::add(vector<vector<float>> e) {
  data.push_back(e);
}

void FilterEnergy::add(vector<vector<uint8_t>>* e) {
  vector<vector<float>> f = vector<vector<float>>(e->size());
  for (int r = 0; r < e->size(); r++) {
    f.at(r) = vector<float>(e->at(0).size());
  }
  
  for (int r = 0; r < e->size(); r++) {
    for (int c = 0; c < e->at(0).size(); c++) {
      f.at(r).at(c) = (float) e->at(r).at(c);
    }
  }
  
  data.push_back(f);
}

void FilterEnergy::normalize() {
  // Assume the first data is the L5'L5 energy response
//  pair<float, float> d_min_max = min_max(0);
//  float global_min = d_min_max.first;
//  float range = d_min_max.second - d_min_max.first;
//  
//  for (int i = 1; i < data.size(); i++) {
//    auto i_data = data.at(i);
//    
//    for (int r = 0; r < i_data.size(); r++) {
//      for (int c = 0; c < i_data.at(0).size(); c++) {
//        float new_data = i_data.at(r).at(c);
//        new_data = new_data / data.at(0).at(r).at(c); //(new_data + global_min) / range * 255;
//        i_data.at(r).at(c) = new_data;
//      }
//    }
//  }
  for (int i = 1; i < data.size(); i++) {
    auto i_data = data.at(i);
    float min = numeric_limits<float>::max();
    float max = numeric_limits<float>::min();
    
    for (int r = 0; r < i_data.size(); r++) {
      for (int c = 0; c < i_data.at(0).size(); c++) {
        float new_data = i_data.at(r).at(c);
        new_data = data.at(0).at(r).at(c) / new_data;
        i_data.at(r).at(c) = new_data;
        data.at(i).at(r).at(c) = new_data;
        
        if (new_data < min) { min = new_data; }
        if (new_data > max) { max = new_data; }
      }
    }
    
    scale(i, min, max);
  }
}

void FilterEnergy::scale(int i, float min, float max) {
  float range = max - min;
  
  for (int r = 0; r < data.at(i).size(); r++) {
    for (int c = 0; c < data.at(i).at(0).size(); c++) {
      float d = data.at(i).at(r).at(c);
      d = (d - min) / range * 255.0;
      data.at(i).at(r).at(c) = d;
    }
  }
}

pair<float, float> FilterEnergy::min_max(int i) {
  vector<vector<float>> v = data.at(i);
  float min = numeric_limits<float>::max();
  float max = numeric_limits<float>::min();
  
  for (int r = 0; r < v.size(); r++) {
    for (int c = 0; c < v.at(0).size(); c++) {
      float s = v.at(r).at(c);
      
      if (s > max) {
        max = s;
      }
      
      if (s < min) {
        min = s;
      }
    }
  }
  
  return pair<float, float>(min, max);
}

Mat FilterEnergy::generate_kmeans(int x, int y, int label_count) {
  Mat m = Mat::zeros(x * y, 24, CV_32F);
  Mat projection_result;
  Mat best_labels;
  
  for (int i = 1; i < data.size(); i++) {
    int z = 0;
    for (int r = 0; r < data.at(i).size(); r++) {
      for (int c = 0; c < data.at(i).at(0).size(); c++) {
        m.at<float>(z, i) = data.at(i).at(r).at(c);
        z++;
      }
    }
  }
  
//  PCA pca = PCA(m, Mat(), PCA::DATA_AS_ROW);
//  pca.project(m, projection_result);
//  kmeans
  kmeans(m, label_count, best_labels, TermCriteria(TermCriteria::EPS, 4000, 0.0001), 80, KMEANS_RANDOM_CENTERS);
  return best_labels;
}

vector<vector<uint8_t>> FilterEnergy::unwrap_kmeans(Mat m, int cols, int levels) {
  vector<vector<uint8_t>> result = vector<vector<uint8_t>>();
  
  int col_counter = 0;
  vector<uint8_t> result_row = vector<uint8_t>();
  for (auto i = m.begin<uint8_t>(); i != m.end<uint8_t>(); ++i) {
    
    result_row.push_back(*i * (255 / (levels - 1)));
    
    if (col_counter % cols == cols - 1) {
      result.push_back(result_row);
      result_row = vector<uint8_t>();
    }
    
    col_counter++;
  }
  
  return result;
}