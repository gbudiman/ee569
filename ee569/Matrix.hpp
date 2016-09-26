//
//  Matrix.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/20/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include "main.hpp"

class Matrix {
public:
  Matrix(std::vector<std::vector<float>>);
  Matrix(std::vector<float>, int);
  std::vector<std::vector<float>> data;
  Matrix multiply(Matrix);
  float multiply_and_average(Matrix);
  
  void thresholdize();
  int erode(Matrix);
  bool exceed_threshold(float);
private:
};

#endif /* Matrix_hpp */
