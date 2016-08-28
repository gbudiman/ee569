//
//  CmykPixel.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef CmykPixel_hpp
#define CmykPixel_hpp

#include "main.hpp"

class CmykPixel {
public:
  CmykPixel(uint8_t, uint8_t, uint8_t);
  
  uint8_t c;
  uint8_t m;
  uint8_t y;
};

#endif /* CmykPixel_hpp */
