//
//  HslPixel.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef HslPixel_hpp
#define HslPixel_hpp

#include "main.hpp"

class HslPixel {
public:
  HslPixel(uint8_t, uint8_t, uint8_t);

  uint8_t h;
  uint8_t s;
  uint8_t l;
};

#endif /* HslPixel_hpp */
