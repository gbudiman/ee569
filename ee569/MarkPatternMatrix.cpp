//
//  MarkPatternMatrix.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/28/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Matrix.hpp"
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

bool MarkPatternMatrix::match(Matrix img, Matrix mark) {
  int z_var = 0;
  int has_non_zero = 0;
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      int mask_type = data.at(r).at(c);
      int img_cell = img.data.at(r).at(c) > 127 ? 1 : 0;
      int mark_cell = mark.data.at(r).at(c);
      
      switch (mask_type) {
        case MCZ:
          if (img_cell != 0) { return false; } break;
        case MCM:
          if (mark_cell != MCM) { return false; } break;
        case MCA:
          z_var++;
          if (img_cell != 0) { has_non_zero++; } break;
          break;
        case MCB:
          z_var++;
          if (img_cell != 0) { has_non_zero++; } break;
          break;
        case MCC:
          z_var++;
          if (img_cell != 0) { has_non_zero++; } break;
          break;
      }
    }
  }
  
  if (z_var > 0 && has_non_zero == 0) {
    return false;
  }
  
  return true;
}