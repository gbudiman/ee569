//
//  FilterEnergy.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/13/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "FilterEnergy.hpp"
using namespace std;

FilterEnergy::FilterEnergy() {
  data = vector<vector<vector<float>>>();
}

void FilterEnergy::add(vector<vector<float>> e) {
  data.push_back(e);
}

void FilterEnergy::normalize() {
  // Assume the first data is the L5'L5 energy response
  
  for (int i = 0; i < data.size(); i++) {
    pair<float, float> p = min_max(i);
    printf("%3d: (%9.1f.. %9.1f)\n", i, p.first, p.second);
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