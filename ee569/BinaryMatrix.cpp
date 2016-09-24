//
//  BinaryMatrix.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/23/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Matrix.hpp"
#include "BinaryMatrix.hpp"
using namespace std;

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