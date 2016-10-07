//
//  Tracer.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/1/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef Tracer_hpp
#define Tracer_hpp

#include "main.hpp"
#include "Coordinate.hpp"

class Tracer {
public:
  Tracer(std::vector<std::vector<uint8_t>>*);
  void add(int, int);
  
  // Format:
  // Trace[0]
  //   
  std::vector<std::vector<Coordinate>> data;
  std::vector<std::vector<uint8_t>> *picture_data;
  
private:
  bool check_existing_trace(int, int);
  void trace(int, int);
  bool has_connecting_pixel(int, int);
  bool not_in_traced_pixels(int, int);
  std::vector<Coordinate> traced_pixels;
};

#endif /* Tracer_hpp */
