//
//  TransferFunction.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/29/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "TransferFunction.hpp"
using namespace std;

TransferFunction::TransferFunction(string _path, Picture *_a, Picture *_b, uint8_t _type) {
  a = _a;
  b = _b;
  path = _path;
  type = _type;
}

void TransferFunction::prepare_gnu_plot() {
  switch (type) {
    case COLOR_GRAY:
      generate_transfer_function_gray();
  }
}

void TransferFunction::generate_transfer_function_gray() {
  for (int i = 0; i < a->hist_gray->data->size(); i++) {
    printf("(%d) %d -> %d\n", i, a->hist_gray->data->at(i), b->hist_gray->data->at(i));
  }
}