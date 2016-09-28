//
//  BinaryMatrix.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/23/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "BinaryMatrix.hpp"
using namespace std;

BinaryMatrix::BinaryMatrix(bool a0, bool a1, bool a2, bool a3, bool a4, bool a5, bool a6, bool a7, bool a8) {
  data = vector<vector<bool>>();
  vector<bool> r1 = { a0, a1, a2};
  vector<bool> r2 = { a3, a4, a5};
  vector<bool> r3 = { a6, a7, a8};
  
  data.push_back(r1);
  data.push_back(r2);
  data.push_back(r3);
}

BinaryMatrix::BinaryMatrix(vector<bool> input, int columns) {
  data = vector<vector<bool>>();
  
  int col_count = 0;
  vector<bool> row_data = vector<bool>();
  for (int i = 0; i < input.size(); i++) {
    row_data.push_back(input.at(i));
    
    if (++col_count % columns == 0) {
      data.push_back(row_data);
      row_data = vector<bool>();
    }
  }
}

bool BinaryMatrix::match(Matrix img) {
  int row_count = img.data.size();
  int col_count = img.data.at(0).size();
  
  for (int r = 0; r < row_count; r++) {
    for (int c = 0; c < col_count; c++) {
      if (data.at(r).at(c) == 0 && img.data.at(r).at(c) < 127) {
        
      } else if (data.at(r).at(c) == 1 && img.data.at(r).at(c) > 127) {
        
      } else {
        return false;
      }
    }
  }
  
  return true;
}

void BinaryMatrix::debug_3x3() {
  for (int r = 0; r < 3; r++) {
    printf("%d %d %d\n", data.at(r).at(0) ? 1 : 0, data.at(r).at(1) ? 1 : 0, data.at(r).at(2) ? 1 : 0);
  }
  printf("\n");
}

