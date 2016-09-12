//
//  PatchCell.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef PatchCell_hpp
#define PatchCell_hpp

#include "main.hpp"
#include "RgbPixel.hpp"

class PatchCell {
public:
  PatchCell(float, RgbPixel *);
  float distance;
  RgbPixel *pixel_data;
};


#endif /* PatchCell_hpp */
