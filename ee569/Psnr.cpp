//
//  Psnr.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Psnr.hpp"
using namespace std;

Psnr::Psnr(Picture *_a, Picture *_b) {
  a = _a;
  b = _b;
}

void Psnr::compute() {
  uint32_t dim_x = a->get_dim_x();
  uint32_t dim_y = a->get_dim_y();
  uint32_t type = a->get_type();
  
  float mse_sum_red = 0;
  float mse_sum_green = 0;
  float mse_sum_blue = 0;
  
  switch (type) {
    case COLOR_RGB:
      for (int c = 0; c < dim_y; c++) {
        for (int r = 0; r < dim_x; r++) {
          RgbPixel pixel_a = a->get_rgb_data()->at(c)->at(r);
          RgbPixel pixel_b = b->get_rgb_data()->at(c)->at(r);
          
          mse_sum_red += pow((pixel_a.r - pixel_b.r), 2);
          mse_sum_green += pow((pixel_a.g - pixel_b.g), 2);
          mse_sum_blue += pow((pixel_a.b - pixel_b.b), 2);
        }
      }
      
      mse_sum_red = mse_sum_red / (dim_x * dim_y);
      mse_sum_green = mse_sum_green / (dim_x * dim_y);
      mse_sum_blue = mse_sum_blue / (dim_x * dim_y);
      
      psnr_red = 10 * log10(MAX_SQUARED / mse_sum_red);
      psnr_green = 10 * log10(MAX_SQUARED / mse_sum_green);
      psnr_blue = 10 * log10(MAX_SQUARED / mse_sum_blue);
      
      printf("PSNR R: %.3f G: %.3f B: %.3f\n", psnr_red, psnr_green, psnr_blue);
      break;
  }
  
  
}