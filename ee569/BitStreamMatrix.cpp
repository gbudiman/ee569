//
//  BitStreamMatrix.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/29/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "BitStreamMatrix.hpp"

int BitStreamMatrix::pack(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
  int result = 0;
  
  result += (a << 8)
         +  (b << 7)
         +  (c << 6)
         +  (d << 5)
         +  (e << 4)
         +  (f << 3)
         +  (g << 2)
         +  (h << 1)
         +  (i << 0);
  return result;
}

int BitStreamMatrix::pack(BinaryMatrix m) {
  int result = 0;
  int left_shifter = 8;
  
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      result += (m.data.at(r).at(c) ? 1 : 0) << left_shifter--;
    }
  }
  
  return result;
}