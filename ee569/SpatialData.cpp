//
//  SpatialData.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/1/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "SpatialData.hpp"

SpatialData::SpatialData() {
  spatial_center = Coordinate(-1, -1);
  bounding_box = BoundingBox();
  area = -1;
  length = -1;
  width = -1;
  chroma = RgbPixel(0,0,0);
}

void SpatialData::update_area(Coordinate _center, float _area) {
  spatial_center = _center;
  area = _area;
}

void SpatialData::update_length(BoundingBox _bb, float _length) {
  bounding_box = _bb;
  length = _length;
}

void SpatialData::update_width() {
  width = area / length;
}