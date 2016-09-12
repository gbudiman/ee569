//
//  NlmWeight.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef NlmWeight_hpp
#define NlmWeight_hpp

#include "main.hpp"

class NlmWeight {
public:
  NlmWeight(int, int, float);
  
  int row;
  int col;
  float weight;
};

#endif /* NlmWeight_hpp */
