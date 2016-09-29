//
//  BinaryMatrix.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/23/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef BinaryMatrix_hpp
#define BinaryMatrix_hpp

#include "main.hpp"
#include "Matrix.hpp"


class BinaryMatrix {
public:
  BinaryMatrix(std::vector<bool>, int);
  BinaryMatrix(bool, bool, bool, bool, bool, bool, bool, bool, bool);
  bool match(Matrix);
  bool strict_match(Matrix);
  
  std::vector<std::vector<bool>> data;
  
  void debug_3x3();
};

#endif /* BinaryMatrix_hpp */
