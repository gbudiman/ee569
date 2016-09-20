//
//  RgbPixel.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef RgbPixel_hpp
#define RgbPixel_hpp

#include "main.hpp"
#include "CmykPixel.hpp"
#include "HslPixel.hpp"

class RgbPixel {
public:
  RgbPixel(uint8_t, uint8_t, uint8_t);
  CmykPixel to_cmyk();
  HslPixel to_hsl();
  
  uint8_t r;
  uint8_t g;
  uint8_t b;
  
  bool is_white();
};

#endif /* RgbPixel_hpp */
