//
//  MorphMatrix.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/28/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef MorphMatrix_hpp
#define MorphMatrix_hpp

#include "main.hpp"
#include "BinaryMatrix.hpp"
using namespace std;

class MorphMatrix {
public:
  MorphMatrix();
  
  vector<BinaryMatrix> thinning;
  vector<BinaryMatrix> shrinking;
  vector<BinaryMatrix> skeletonizing;
  
  void debug_matrix(int);
};

#endif