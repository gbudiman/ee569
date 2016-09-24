//
//  GrainCategorizer.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/24/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef GrainCategorizer_hpp
#define GrainCategorizer_hpp

#include "main.hpp"
#include "Coordinate.hpp"

class GrainCategorizer {
public:
  GrainCategorizer();
  void add(int, int);
  int count_groups();
  void debug_groups();
  
  std::vector<std::vector<Coordinate>> grains;
  
private:
};

#endif /* GrainCategorizer_hpp */
