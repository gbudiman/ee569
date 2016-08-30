//
//  Histogram.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/28/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef Histogram_hpp
#define Histogram_hpp

#include "main.hpp"

class Histogram {
public:
  Histogram();
  void push(uint8_t);
  void update_at(uint8_t, uint32_t);
  void debug();
  void plot();
  void plot(uint8_t);
  
  void generate_gaussian(uint32_t, uint32_t, uint32_t, uint32_t);
  
  std::vector<uint32_t> *data;
};

#endif /* Histogram_hpp */
