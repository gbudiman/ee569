//
//  Coordinate.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/24/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef Coordinate_hpp
#define Coordinate_hpp

#include "main.hpp"

class Coordinate {
public:
  Coordinate(int, int);
  bool has_connectivity(Coordinate);
  bool operator==(const Coordinate&);
  bool operator!=(const Coordinate&);
  
  void move(int);
  
  uint32_t to_scalar();
  int row;
  int col;
};

#endif /* Coordinate_hpp */
