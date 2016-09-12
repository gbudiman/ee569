//
//  PatchCell.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "PatchCell.hpp"

PatchCell::PatchCell(float _distance, RgbPixel *_pixel_data) {
  distance = _distance;
  pixel_data = _pixel_data;
}