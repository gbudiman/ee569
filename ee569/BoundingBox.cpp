//
//  BoundingBox.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/1/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "BoundingBox.hpp"

BoundingBox::BoundingBox() {
  r_min = 0x7FFF;
  r_max = -1;
  c_min = 0x7FFF;
  c_max = -1;
}

void BoundingBox::update(Coordinate coord) {
  BoundingBox::update(coord.row, coord.col);
}

void BoundingBox::update(int r, int c) {
  if (r > r_max) { r_max = r; }
  if (r < r_min) { r_min = r; }
  if (c > c_max) { c_max = c; }
  if (c < c_min) { c_min = c; }
}

bool BoundingBox::in_bounding_box(int r, int c) {
  return (r_min <= r && r <= r_max && c_min <= c && c <= c_max);
}

bool BoundingBox::in_bounding_box(Coordinate coord) {
  return in_bounding_box(coord.row, coord.col);
}

void BoundingBox::dump() {
  float length = get_length();
  printf("(%3d, %3d) -> (%3d, %3d): L = %5.2f", r_min, c_min, r_max, c_max, length);
}

float BoundingBox::get_length() {
  float r_diff = (float) r_max - (float) r_min;
  float c_diff = (float) c_max - (float) c_min;
  
  float length = sqrtf(r_diff * r_diff + c_diff * c_diff);
  return length;
}