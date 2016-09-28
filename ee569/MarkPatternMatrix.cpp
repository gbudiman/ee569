//
//  MarkPatternMatrix.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/28/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "MarkPatternMatrix.hpp"
using namespace std;

MarkPatternMatrix::MarkPatternMatrix(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
  data = vector<vector<int>>();
  
  vector<int> r1 = { a0, a1, a2};
  vector<int> r2 = { a3, a4, a5};
  vector<int> r3 = { a6, a7, a8};
  
  data.push_back(r1);
  data.push_back(r2);
  data.push_back(r3);
}

void MarkPatternMatrix::debug_3x3() {
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      int d = data.at(r).at(c);
      char x;
      
      switch (d) {
        case MCA: x = 'A'; break;
        case MCB: x = 'B'; break;
        case MCC: x = 'C'; break;
        case MCD: x = 'D'; break;
        case MCM: x = 'M'; break;
        default: x = '0';
      }
      
      printf("%c ", x);
    }
    
    printf("\n");
  }
  
  printf("\n");
}