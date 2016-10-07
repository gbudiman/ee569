//
//  MarkPatternMatrix.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/28/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef MarkPatternMatrix_hpp
#define MarkPatternMatrix_hpp

#include "main.hpp"

class MarkPatternMatrix {
public:
  MarkPatternMatrix(int, int, int, int, int, int, int, int, int);
  void debug_3x3();
  bool match(Matrix, Matrix);
  
  std::vector<std::vector<int>> data;
};

#endif /* MarkPatternMatrix_hpp */
