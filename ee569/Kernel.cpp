//
//  Kernel.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Kernel.hpp"
using namespace std;

Kernel::Kernel(int _radius, float sigma) {
  radius = _radius;
  make_kernel(sigma);
}

void Kernel::make_kernel(float sigma) {
  const float pi = 3.1415927;
  float sum = 0;
  kernel = vector<float>();
  
  for (int i = 0 - radius; i <= radius; i++) {
    float t1 = 1.0f / sqrt(2 * pi * sigma);
    float t2_up = i * i / ( 2 * sigma * sigma );
    float expr = exp(-t2_up);
    float aval = t1 * expr;
    
    sum += aval;
    kernel.push_back(aval);
  }
  
  for (int i = 0; i < kernel.size(); i++) {
    kernel.at(i) = kernel.at(i) / sum;
  }
}

void Kernel::test_unit_convolve() {
  vector<vector<uint8_t>> test_image = vector<vector<uint8_t>>();
  for (int i = -radius; i <= radius; i++) {
    vector<uint8_t> row = vector<uint8_t>();
    
    for (int j = -radius; j <= radius; j++) {
      row.push_back(127);
    }
    
    test_image.push_back(row);
  }
  
  convolve(test_image);
}

void Kernel::test_convolve() {
  vector<vector<uint8_t>> test_image = vector<vector<uint8_t>>();
  
  vector<uint8_t> row = vector<uint8_t>();
  row.push_back(20);
  row.push_back(40);
  row.push_back(80);
  test_image.push_back(row);
  
  row = vector<uint8_t>();
  row.push_back(80);
  row.push_back(40);
  row.push_back(80);
  test_image.push_back(row);
  
  row = vector<uint8_t>();
  row.push_back(120);
  row.push_back(240);
  row.push_back(80);
  test_image.push_back(row);
  
  convolve(test_image);
}

uint8_t Kernel::convolve(vector<vector<uint8_t>> img) {
  //vector<vector<uint8_t>> result = vector<vector<uint8_t>>();
  float original_energy = 0;
  float csum = 0;
  vector<float> first_pass = vector<float>();
  
  for (int r = 0; r < radius * 2 + 1; r++) {
    vector<uint8_t> row_data = img.at(r);
    float isum = 0;
    
    for (int c = 0; c < radius * 2 + 1; c++) {
      isum += (float) row_data.at(c) * kernel.at(c);
    }
    
    first_pass.push_back(isum);
  }
  
  for (int fpk = 0; fpk < radius * 2 + 1; fpk++) {
    //vector<uint8_t> row_data = vector<uint8_t>();
    for (int k = 0; k < radius * 2 + 1; k++) {
      //row_data.push_back(first_pass.at(fpk) * kernel.at(k));
      //printf("%f * %f = %f\n", first_pass.at(fpk), kernel.at(k), first_pass.at(fpk) * kernel.at(k));
      csum += first_pass.at(fpk) * kernel.at(k) * img.at(fpk).at(k);
      original_energy += img.at(fpk).at(k);
    }
    //result.push_back(row_data);
  }
  
  return csum * (radius * 2 + 1) / original_energy;
}