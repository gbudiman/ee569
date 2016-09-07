//
//  Kernel.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef Kernel_hpp
#define Kernel_hpp

#include "main.hpp"
#include "Histogram.hpp"
#include "RgbPixel.hpp"
#include "Histogram.hpp"

class Kernel {
public:
  Kernel(int, float);
  void make_kernel(float);
  void test_convolve();
  void test_unit_convolve();
  uint8_t convolve(std::vector<std::vector<uint8_t>> image);
  
  std::vector<float> kernel;
  int radius;
};

#endif /* Kernel_hpp */
