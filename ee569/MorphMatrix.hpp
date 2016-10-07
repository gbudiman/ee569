//
//  MorphMatrix.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/28/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef MorphMatrix_hpp
#define MorphMatrix_hpp

#include "main.hpp"
#include "Matrix.hpp"
#include "BinaryMatrix.hpp"
#include "MarkPatternMatrix.hpp"
#include "BitStreamMatrix.hpp"
using namespace std;

class MorphMatrix {
public:
  MorphMatrix();
  
  vector<BinaryMatrix> thinning;
  vector<BinaryMatrix> shrinking;
  vector<BinaryMatrix> skeletonizing;
  vector<MarkPatternMatrix> stump;
  vector<MarkPatternMatrix> skump;
  
  vector<int> thinning_bitstream;
  vector<int> shrinking_bitstream;
  vector<int> skeletonizing_bitstream;
  
  void debug_matrix(int);
  void debug_type2_filter();
  void debug_skel2_filter();
  
  //int thinning_hit_or_miss(Matrix);
  bool thinning_first_filter(int);
  bool skeletonizing_first_filter(int);
  bool eroding_first_filter(int);
  bool thinning_unconditional_filter(Matrix, Matrix);
  bool skeletonizing_unconditional_filter(Matrix, Matrix);
  bool eroding_unconditional_filter(Matrix, Matrix);
private:
  
};

#endif