//
//  BoundingBox.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/1/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef BoundingBox_hpp
#define BoundingBox_hpp

#include "main.hpp"
#include "Coordinate.hpp"

class BoundingBox {
public:
  BoundingBox();
  void update(int r, int c);
  void update(Coordinate coord);
  bool in_bounding_box(int r, int c);
  bool in_bounding_box(Coordinate);
  int r_min, r_max, c_min, c_max;
  
  void dump();
  
  float get_length();
private:
};

#endif /* BoundingBox_hpp */
