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
  std::vector<std::vector<float>> data;
  Matrix multiply(Matrix);
  float multiply_and_average(Matrix);
  
  void thresholdize();
private:
};

#endif /* Matrix_hpp */
