//
//  TransferFunction.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/29/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "TransferFunction.hpp"
using namespace std;

TransferFunction::TransferFunction() {
  initialize(256);
}

TransferFunction::TransferFunction(uint32_t bin_size) {
  initialize(bin_size);
}

void TransferFunction::initialize(uint32_t bin_size) {
  data = new vector<int16_t>(bin_size);
  
  for (uint32_t i = 0; i < bin_size; i++) {
    data->at(i) = -1;
  }
}

void TransferFunction::generate_linear(int a, int b, int x, int y) {
  float gradient = (float) (y - b) / (float) (x - a);
  
  for (int i = a; i <= x; i++) {
    data->at(i) = b + (i - a) * gradient;
  }
}