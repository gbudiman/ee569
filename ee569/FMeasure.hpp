//
//  FMeasure.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/17/16.
//  Finalized on 10/31/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef FMeasure_hpp
#define FMeasure_hpp

#include "main.hpp"
#include "Picture.hpp"

class FMeasure {
public:
  FMeasure(Picture);
  void compare_against(Picture);
  
  Picture base;
  Picture result;
  
private:
  float f_float(int);
  float f_precision(int, int);
  float f_recall(int, int);
  float f_compute(int, int, int, int);
  int dim_x;
  int dim_y;
};

#endif /* FMeasure_hpp */
