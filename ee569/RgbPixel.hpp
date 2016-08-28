//
//  RgbPixel.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef RgbPixel_hpp
#define RgbPixel_hpp

#include "main.hpp"
#include "CmykPixel.hpp"

class RgbPixel {
public:
  RgbPixel(uint8_t, uint8_t, uint8_t);
  CmykPixel to_cmyk();
  
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

#endif /* RgbPixel_hpp */
