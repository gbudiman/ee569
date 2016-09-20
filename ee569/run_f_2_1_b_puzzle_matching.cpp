//
//  run_f_2_1_b_puzzle_matching.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/20/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"

void f_2_1_b_puzzle_matching() {
  Picture* puzzles = new Picture("hw2_images/Piece.raw", 500, 500, COLOR_RGB);
  puzzles->find_piece();
}
