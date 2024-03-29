//
//  BoundaryTracer.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/1/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef BoundaryTracer_hpp
#define BoundaryTracer_hpp

#include "main.hpp"
#include "Coordinate.hpp"

class BoundaryTracer {
public:
  BoundaryTracer(int, int);
  
  void set_initial_point(Coordinate);
  bool trace(int, int&, int&);
  std::vector<Coordinate> traced;
  std::vector<std::vector<uint8_t>> cols;
private:
  Coordinate initial_point = Coordinate(-1, -1);
  uint8_t entrance;
  bool is_already_traced(Coordinate);
};

#endif /* BoundaryTracer_hpp */
