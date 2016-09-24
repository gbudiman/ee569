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

class BinaryMatrix {
public:
  BinaryMatrix(std::vector<bool>, int);
  bool match(Matrix);
  
  std::vector<std::vector<bool>> data;
};

#endif /* BinaryMatrix_hpp */
