//
//  SpatialData.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/1/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef SpatialData_hpp
#define SpatialData_hpp

#include "main.hpp"
#include "Coordinate.hpp"
#include "BoundingBox.hpp"

class SpatialData {
public:
  SpatialData();
  
  void update_area(Coordinate, float);
  void update_length(BoundingBox, float);
  void update_width();
  
  Coordinate spatial_center = Coordinate(-1,-1);
  BoundingBox bounding_box;
  float area;
  float length;
  float width;
};

#endif /* SpatialData_hpp */
