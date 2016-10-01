//
//  Tracer.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/1/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Tracer.hpp"
using namespace std;

Tracer::Tracer(vector<vector<uint8_t>>* _picture_data) {
  data = vector<vector<Coordinate>>();
  
  picture_data = new vector<vector<uint8_t>>();
  
  for (int r = 0; r < _picture_data->size(); r++) {
    vector<uint8_t> row_data(_picture_data->at(r));
    picture_data->push_back(row_data);
  }
}

void Tracer::add(int r, int c) {
  //printf("processing (%d, %d)\n", r, c);

  if (!check_existing_trace(r, c)) {
    //printf("  Trace begin from (%d, %d)\n", r, c);
    traced_pixels = vector<Coordinate>();
    trace(r, c);
    
    data.push_back(traced_pixels);
  }
}

void Tracer::trace(int r, int c) {
  for (int rr = r - 1; rr <= r + 1; rr++) {
    for (int cc = c - 1; cc <= c + 1; cc++) {
      if (rr == r && cc == c) { continue; }
      
      if (has_connecting_pixel(rr, cc) && not_in_traced_pixels(rr, cc)) {
        //printf("    Adding trace of pixel (%d, %d)\n", rr, cc);
        traced_pixels.push_back(Coordinate(rr, cc));
        trace(rr, cc);
      }
    }
  }
}

bool Tracer::check_existing_trace(int r, int c) {
  for (int i = 0; i < data.size(); i++) {
    for (int e = data.at(i).size() - 1; e >= 0; e--) {
      int e_row = data.at(i).at(e).row;
      int e_col = data.at(i).at(e).col;
      
      if (e_row == r && e_col == c) { return true; }
    }
  }
  
  return false;
}

bool Tracer::not_in_traced_pixels(int r, int c) {
  for (int i = 0; i < traced_pixels.size(); i++) {
    Coordinate traced = traced_pixels.at(i);
    if (r == traced.row && c == traced.col) {
      return false;
    }
  }
  
  return true;
}

bool Tracer::has_connecting_pixel(int r, int c) {
  return picture_data->at(r).at(c) == 0xFF;
}