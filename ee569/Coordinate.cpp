//
//  Coordinate.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/24/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Coordinate.hpp"

Coordinate::Coordinate(int r, int c) {
  row = r;
  col = c;
}

bool Coordinate::has_connectivity(Coordinate other) {
//  if (abs(other.row - row) <= 3 && abs(other.col - col) <= 3) {
//    return true;
//  }
  int diff_row = (other.row - row) * (other.row - row);
  int diff_col = (other.col - col) * (other.col - col);
  
  if (diff_row + diff_col < 52) {
    return true;
  }
  
  return false;
}

bool Coordinate::operator==(const Coordinate &other) {
  return (row == other.row && col == other.col);
}

bool Coordinate::operator!=(const Coordinate &other) {
  return !(row == other.row && col == other.col);
}

void Coordinate::move(int direction) {
  switch(direction) {
    case SCAN_DIR_UP: row--; break;
    case SCAN_DIR_DOWN: row++; break;
    case SCAN_DIR_LEFT: col--; break;
    case SCAN_DIR_RIGHT: col++; break;
  }
}

uint32_t Coordinate::to_scalar() {
  return ((row << 16) | col);
}