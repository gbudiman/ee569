//
//  BoundaryTracer.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/1/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "BoundaryTracer.hpp"
using namespace std;

BoundaryTracer::BoundaryTracer(int row, int col) {
  traced = vector<Coordinate>();
  entrance = 7;
  
  cols = vector<vector<uint8_t>>(row);
  for (int c = 0; c < col; c++) {
    vector<uint8_t> col_row = vector<uint8_t>();
    cols.push_back(col_row);
  }
}

void BoundaryTracer::set_initial_point(Coordinate coord) {
  initial_point = coord;
  traced.push_back(coord);
}

bool BoundaryTracer::trace(int mat, int &r, int &c) {
  vector<int> zmat = { mat & 0b100000000,
                       mat & 0b010000000,
                       mat & 0b001000000,
                       mat & 0b000001000,
                       mat & 0b000000001,
                       mat & 0b000000010,
                       mat & 0b000000100,
                       mat & 0b000100000 };

  entrance = (entrance + 1) & 0b111;
  while (zmat.at(entrance) == 0) {
    entrance = (entrance + 1) & 0b111;
  }
  
  switch(entrance) {
    case 0: r--; c--; break;
    case 1: r--;      break;
    case 2: r--; c++; break;
    case 3:      c++; break;
    case 4: r++; c++; break;
    case 5: r++;      break;
    case 6: r++; c--; break;
    case 7:      c--; break;
  }
  
  Coordinate new_position = Coordinate(r, c);
  //if (!is_already_traced(new_position)) {
  if (new_position != initial_point) {
    traced.push_back(new_position);
    entrance = (entrance + 4) & 0b111;
    
    vector<uint8_t> col_tracker = cols.at(r);
    if (col_tracker.size() == 0) {
      cols.at(r).push_back(c);
    } else {
      uint8_t last_col_at_this_row = cols.at(r).back();
      if (abs(last_col_at_this_row - c) < 3) {
        cols.at(r).back() = c;
      } else {
        cols.at(r).push_back(c);
      }
    }

    return true;
  }
  
  return false;
}

bool BoundaryTracer::is_already_traced(Coordinate coord) {
  for (int i = 0; i < traced.size(); i++) {
    if (traced.at(i) == coord) { return true; }
  }
  
  return false;
}