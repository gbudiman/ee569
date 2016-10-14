//
//  FilterEnergy.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/13/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef FilterEnergy_hpp
#define FilterEnergy_hpp

#include "main.hpp"

class FilterEnergy {
public:
  FilterEnergy();
  void add(std::vector<std::vector<float>>);
  void normalize();
  std::pair<float, float> min_max(int);
  
private:
  std::vector<std::vector<std::vector<float>>> data;
};

#endif /* FilterEnergy_hpp */
