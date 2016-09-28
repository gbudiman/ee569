//
//  MorphMatrix.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/28/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "MorphMatrix.hpp"

MorphMatrix::MorphMatrix() {
  thinning = vector<BinaryMatrix>();
  shrinking = vector<BinaryMatrix>();
  skeletonizing = vector<BinaryMatrix>();
  
  BinaryMatrix b_1a1 = BinaryMatrix(0, 0, 1, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_1a2 = BinaryMatrix(1, 0, 0, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_1a3 = BinaryMatrix(0, 0, 0, 0, 1, 0, 1, 0, 0);
  BinaryMatrix b_1a4 = BinaryMatrix(0, 0, 0, 0, 1, 0, 0, 0, 1);
  
  BinaryMatrix b_2a1 = BinaryMatrix(0, 0, 0, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_2a2 = BinaryMatrix(0, 1, 0, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_2a3 = BinaryMatrix(0, 0, 0, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_2a4 = BinaryMatrix(0, 0, 0, 0, 1, 0, 0, 1, 0);
  
  BinaryMatrix b_3a1 = BinaryMatrix(0, 0, 1, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_3a2 = BinaryMatrix(0, 1, 1, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_3a3 = BinaryMatrix(1, 1, 0, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_3a4 = BinaryMatrix(1, 0, 0, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_3a5 = BinaryMatrix(0, 0, 0, 1, 1, 0, 1, 0, 0);
  BinaryMatrix b_3a6 = BinaryMatrix(0, 0, 0, 0, 1, 0, 1, 1, 0);
  BinaryMatrix b_3a7 = BinaryMatrix(0, 0, 0, 0, 1, 0, 0, 1, 1);
  BinaryMatrix b_3a8 = BinaryMatrix(0, 0, 0, 0, 1, 1, 0, 0, 1);
  
  BinaryMatrix b_4a1 = BinaryMatrix(0, 1, 0, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_4a2 = BinaryMatrix(0, 1, 0, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_4a3 = BinaryMatrix(0, 0, 0, 1, 1, 0, 0, 1, 0);
  BinaryMatrix b_4a4 = BinaryMatrix(0, 0, 0, 0, 1, 1, 0, 1, 0);
  
  BinaryMatrix b_4b1 = BinaryMatrix(0, 0, 1, 0, 1, 1, 0, 0, 1);
  BinaryMatrix b_4b2 = BinaryMatrix(1, 1, 1, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_4b3 = BinaryMatrix(1, 0, 0, 1, 1, 0, 1, 0, 0);
  BinaryMatrix b_4b4 = BinaryMatrix(0, 0, 0, 0, 1, 0, 1, 1, 1);
  
  BinaryMatrix b_5a1 = BinaryMatrix(1, 1, 0, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_5a2 = BinaryMatrix(0, 1, 0, 0, 1, 1, 0, 0, 1);
  BinaryMatrix b_5a3 = BinaryMatrix(0, 1, 1, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_5a4 = BinaryMatrix(0, 0, 1, 0, 1, 1, 0, 1, 0);
  
  BinaryMatrix b_5b1 = BinaryMatrix(0, 1, 1, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_5b2 = BinaryMatrix(1, 1, 0, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_5b3 = BinaryMatrix(0, 0, 0, 1, 1, 0, 1, 1, 0);
  BinaryMatrix b_5b4 = BinaryMatrix(0, 0, 0, 0, 1, 1, 0, 1, 1);
  
  BinaryMatrix b_6a1 = BinaryMatrix(1, 1, 0, 0, 1, 1, 0, 0, 1);
  BinaryMatrix b_6a2 = BinaryMatrix(0, 1, 1, 1, 1, 0, 1, 0, 0);
  
  BinaryMatrix b_6b1 = BinaryMatrix(1, 1, 1, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_6b2 = BinaryMatrix(0, 1, 1, 0, 1, 1, 0, 0, 1);
  BinaryMatrix b_6b3 = BinaryMatrix(1, 1, 1, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_6b4 = BinaryMatrix(1, 1, 0, 1, 1, 0, 1, 0, 0);
  BinaryMatrix b_6b5 = BinaryMatrix(1, 0, 0, 1, 1, 0, 1, 1, 0);
  BinaryMatrix b_6b6 = BinaryMatrix(0, 0, 0, 1, 1, 0, 1, 1, 1);
  BinaryMatrix b_6b7 = BinaryMatrix(0, 0, 0, 0, 1, 1, 1, 1, 1);
  BinaryMatrix b_6b8 = BinaryMatrix(0, 0, 1, 0, 1, 1, 0, 1, 1);
  
  BinaryMatrix b_7a1 = BinaryMatrix(1, 1, 1, 0, 1, 1, 0, 0, 1);
  BinaryMatrix b_7a2 = BinaryMatrix(1, 1, 1, 1, 1, 0, 1, 0, 0);
  BinaryMatrix b_7a3 = BinaryMatrix(1, 0, 0, 1, 1, 0, 1, 1, 1);
  BinaryMatrix b_7a4 = BinaryMatrix(0, 0, 1, 0, 1, 1, 1, 1, 1);
  
  BinaryMatrix b_8a1 = BinaryMatrix(0, 1, 1, 0, 1, 1, 0, 1, 1);
  BinaryMatrix b_8a2 = BinaryMatrix(1, 1, 1, 1, 1, 1, 0, 0, 0);
  BinaryMatrix b_8a3 = BinaryMatrix(1, 1, 0, 1, 1, 0, 1, 1, 0);
  BinaryMatrix b_8a4 = BinaryMatrix(0, 0, 0, 1, 1, 1, 1, 1, 1);
  
  BinaryMatrix b_9a1 = BinaryMatrix(1, 1, 1, 0, 1, 1, 0, 1, 1);
  BinaryMatrix b_9a2 = BinaryMatrix(0, 1, 1, 0, 1, 1, 1, 1, 1);
  BinaryMatrix b_9a3 = BinaryMatrix(1, 1, 1, 1, 1, 1, 1, 0, 0);
  BinaryMatrix b_9a4 = BinaryMatrix(1, 1, 1, 1, 1, 1, 0, 0, 1);
  BinaryMatrix b_9a5 = BinaryMatrix(1, 1, 1, 1, 1, 0, 1, 1, 0);
  BinaryMatrix b_9a6 = BinaryMatrix(1, 1, 0, 1, 1, 0, 1, 1, 1);
  BinaryMatrix b_9a7 = BinaryMatrix(1, 0, 0, 1, 1, 1, 1, 1, 1);
  BinaryMatrix b_9a8 = BinaryMatrix(0, 0, 1, 1, 1, 1, 1, 1, 1);
  
  BinaryMatrix b_10a1 = BinaryMatrix(1, 1, 1, 0, 1, 1, 1, 1, 1);
  BinaryMatrix b_10a2 = BinaryMatrix(1, 1, 1, 1, 1, 1, 1, 0, 1);
  BinaryMatrix b_10a3 = BinaryMatrix(1, 1, 1, 1, 1, 0, 1, 1, 1);
  BinaryMatrix b_10a4 = BinaryMatrix(1, 0, 1, 1, 1, 1, 1, 1, 1);
  
  BinaryMatrix b_11a1 = BinaryMatrix(1, 1, 1, 1, 1, 1, 0, 1, 1);
  BinaryMatrix b_11a2 = BinaryMatrix(1, 1, 1, 1, 1, 1, 1, 1, 0);
  BinaryMatrix b_11a3 = BinaryMatrix(1, 1, 0, 1, 1, 1, 1, 1, 1);
  BinaryMatrix b_11a4 = BinaryMatrix(0, 1, 1, 1, 1, 1, 1, 1, 1);
  
  shrinking.push_back(b_1a1);
  shrinking.push_back(b_1a2);
  shrinking.push_back(b_1a3);
  shrinking.push_back(b_1a4);
  shrinking.push_back(b_2a1);
  shrinking.push_back(b_2a2);
  shrinking.push_back(b_2a3);
  shrinking.push_back(b_2a4);
  shrinking.push_back(b_3a1);
  shrinking.push_back(b_3a2);
  shrinking.push_back(b_3a3);
  shrinking.push_back(b_3a4);
  shrinking.push_back(b_3a5);
  shrinking.push_back(b_3a6);
  shrinking.push_back(b_3a7);
  shrinking.push_back(b_3a8);
  
  thinning.push_back(b_4a1);
  thinning.push_back(b_4a2);
  thinning.push_back(b_4a3);
  thinning.push_back(b_4a4);
  skeletonizing.push_back(b_4a1);
  skeletonizing.push_back(b_4a2);
  skeletonizing.push_back(b_4a3);
  skeletonizing.push_back(b_4a4);
  
  shrinking.push_back(b_4b1);
  shrinking.push_back(b_4b2);
  shrinking.push_back(b_4b3);
  shrinking.push_back(b_4b4);
  thinning.push_back(b_4b1);
  thinning.push_back(b_4b2);
  thinning.push_back(b_4b3);
  thinning.push_back(b_4b4);
  skeletonizing.push_back(b_4b1);
  skeletonizing.push_back(b_4b2);
  skeletonizing.push_back(b_4b3);
  skeletonizing.push_back(b_4b4);
  
  shrinking.push_back(b_5a1);
  shrinking.push_back(b_5a2);
  shrinking.push_back(b_5a3);
  shrinking.push_back(b_5a4);
  thinning.push_back(b_5a1);
  thinning.push_back(b_5a2);
  thinning.push_back(b_5a3);
  thinning.push_back(b_5a4);
  shrinking.push_back(b_5b1);
  shrinking.push_back(b_5b2);
  shrinking.push_back(b_5b3);
  shrinking.push_back(b_5b4);
  thinning.push_back(b_5b1);
  thinning.push_back(b_5b2);
  thinning.push_back(b_5b3);
  thinning.push_back(b_5b4);
  
  shrinking.push_back(b_6a1);
  shrinking.push_back(b_6a2);
  thinning.push_back(b_6a1);
  thinning.push_back(b_6a2);
  
  shrinking.push_back(b_6b1);
  shrinking.push_back(b_6b2);
  shrinking.push_back(b_6b3);
  shrinking.push_back(b_6b4);
  shrinking.push_back(b_6b5);
  shrinking.push_back(b_6b6);
  shrinking.push_back(b_6b7);
  shrinking.push_back(b_6b8);
  thinning.push_back(b_6b1);
  thinning.push_back(b_6b2);
  thinning.push_back(b_6b3);
  thinning.push_back(b_6b4);
  thinning.push_back(b_6b5);
  thinning.push_back(b_6b6);
  thinning.push_back(b_6b7);
  thinning.push_back(b_6b8);
  skeletonizing.push_back(b_6b1);
  skeletonizing.push_back(b_6b2);
  skeletonizing.push_back(b_6b3);
  skeletonizing.push_back(b_6b4);
  skeletonizing.push_back(b_6b5);
  skeletonizing.push_back(b_6b6);
  skeletonizing.push_back(b_6b7);
  skeletonizing.push_back(b_6b8);
  
  shrinking.push_back(b_7a1);
  shrinking.push_back(b_7a2);
  shrinking.push_back(b_7a3);
  shrinking.push_back(b_7a4);
  thinning.push_back(b_7a1);
  thinning.push_back(b_7a2);
  thinning.push_back(b_7a3);
  thinning.push_back(b_7a4);
  skeletonizing.push_back(b_7a1);
  skeletonizing.push_back(b_7a2);
  skeletonizing.push_back(b_7a3);
  skeletonizing.push_back(b_7a4);
  
  shrinking.push_back(b_8a1);
  shrinking.push_back(b_8a2);
  shrinking.push_back(b_8a3);
  shrinking.push_back(b_8a4);
  thinning.push_back(b_8a1);
  thinning.push_back(b_8a2);
  thinning.push_back(b_8a3);
  thinning.push_back(b_8a4);
  skeletonizing.push_back(b_8a1);
  skeletonizing.push_back(b_8a2);
  skeletonizing.push_back(b_8a3);
  skeletonizing.push_back(b_8a4);
  
  shrinking.push_back(b_9a1);
  shrinking.push_back(b_9a2);
  shrinking.push_back(b_9a3);
  shrinking.push_back(b_9a4);
  shrinking.push_back(b_9a5);
  shrinking.push_back(b_9a6);
  shrinking.push_back(b_9a7);
  shrinking.push_back(b_9a8);
  thinning.push_back(b_9a1);
  thinning.push_back(b_9a2);
  thinning.push_back(b_9a3);
  thinning.push_back(b_9a4);
  thinning.push_back(b_9a5);
  thinning.push_back(b_9a6);
  thinning.push_back(b_9a7);
  thinning.push_back(b_9a8);
  skeletonizing.push_back(b_9a1);
  skeletonizing.push_back(b_9a2);
  skeletonizing.push_back(b_9a3);
  skeletonizing.push_back(b_9a4);
  skeletonizing.push_back(b_9a5);
  skeletonizing.push_back(b_9a6);
  skeletonizing.push_back(b_9a7);
  skeletonizing.push_back(b_9a8);
  
  shrinking.push_back(b_10a1);
  shrinking.push_back(b_10a2);
  shrinking.push_back(b_10a3);
  shrinking.push_back(b_10a4);
  thinning.push_back(b_10a1);
  thinning.push_back(b_10a2);
  thinning.push_back(b_10a3);
  thinning.push_back(b_10a4);
  skeletonizing.push_back(b_10a1);
  skeletonizing.push_back(b_10a2);
  skeletonizing.push_back(b_10a3);
  skeletonizing.push_back(b_10a4);
  
  skeletonizing.push_back(b_11a1);
  skeletonizing.push_back(b_11a2);
  skeletonizing.push_back(b_11a3);
  skeletonizing.push_back(b_11a4);
}

void MorphMatrix::debug_matrix(int type) {
  vector<BinaryMatrix> v;
  
  switch(type) {
    case MORPH_THINNING: v = thinning; break;
    case MORPH_SHRINKING: v = shrinking; break;
    case MORPH_SKELETONIZING: v = skeletonizing; break;
  }
  
  for (int i = 0; i < v.size(); i++) {
    v.at(i).debug_3x3();
  }
}
