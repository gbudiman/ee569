//
//  GrainCategorizer.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/24/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "GrainCategorizer.hpp"
using namespace std;

GrainCategorizer::GrainCategorizer() {
  grains = vector<vector<Coordinate>>();
}

void GrainCategorizer::add(int r, int c) {
  Coordinate coord = Coordinate(r, c);
  bool group_found = false;
  
  for (int g = 0; g < grains.size(); g++) {
    vector<Coordinate> current_group = grains.at(g);
    
    for (int cg = 0; cg < current_group.size(); cg++) {
      Coordinate cc = current_group.at(cg);
      if (cc.has_connectivity(coord)) {
        group_found = true;
        //printf("%d <= %d, %d\n", g, r, c);
        grains.at(g).push_back(coord);
        break;
      }
    }
    
    if (group_found) {
      break;
    }
  }
  
  if (!group_found) {
    //printf("NEW GROUP: %d, %d\n", r, c);
    vector<Coordinate> new_group = vector<Coordinate>();
    new_group.push_back(coord);
    grains.push_back(new_group);
  }
}

int GrainCategorizer::count_groups() {
  int real_count = 0;
  
  for (int g = 0; g < grains.size(); g++) {
    int group_member_count = grains.at(g).size();
    
    real_count += group_member_count < GRAIN_BORDER_THRESHOLD ? 0 : 1;
  }
  
  return real_count;
}

void GrainCategorizer::debug_groups() {
  int real_count = 0;
  for (int g = 0; g < grains.size(); g++) {
    vector<Coordinate> members = grains.at(g);
    int bb_row_low = 0xFFFF;
    int bb_row_high = 0;
    int bb_col_low = 0xFFFF;
    int bb_col_high = 0;
    
    if (members.size() < GRAIN_BORDER_THRESHOLD) {
      continue;
      //printf(" <<< GROUP %d (NOT COUNTED) >>>\n", g);
    } else {
      printf(" <<< GROUP %d >>>\n", ++real_count);
    }
    
    for (int m = 0; m < members.size(); m++) {
      int this_row = members.at(m).row;
      int this_col = members.at(m).col;
      if (this_row > bb_row_high) {
        bb_row_high = this_row;
      }
      if (this_row < bb_row_low) {
        bb_row_low = this_row;
      }
      if (this_col > bb_col_high) {
        bb_col_high = this_col;
      }
      if (this_col < bb_col_low) {
        bb_col_low = this_col;
      }
      
      //printf("  (%d, %d)\n", this_row, this_col);
    }
    
    printf(" (%d, %d) -> (%d, %d) === (%d, %d)\n", bb_col_low, bb_row_low, bb_col_high, bb_row_high, bb_col_high - bb_col_low, bb_row_high - bb_row_low);
  }
}