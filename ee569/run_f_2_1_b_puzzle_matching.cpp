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
  puzzles->find_piece("hw2_out/hillary_piece.raw", "hw2_out/trump_piece.raw");
  
  Picture *hillary_piece = new Picture("hw2_out/hillary_piece.raw", 101, 101, COLOR_RGB);
  hillary_piece->crop(0, 0, 99, 99);
  hillary_piece->write_to_file("hw2_out/hillary_piece_shrink.raw");
  
  Picture *trump_piece = new Picture("hw2_out/trump_piece.raw", 101, 101, COLOR_RGB);
  trump_piece->crop(0, 0, 99, 99);
  trump_piece->write_to_file("hw2_out/trump_piece_shrink.raw");
  
  int tlcr; int tlcc;
  int brcr; int brcc;
  
  Picture* hillary = new Picture("hw2_images/Hillary.raw", 512, 512, COLOR_RGB);
  hillary->find_hole(&tlcr, &tlcc, &brcr, &brcc);
  hillary->fit_piece(Picture("hw2_out/hillary_piece_shrink.raw", 100, 100, COLOR_RGB), tlcr, tlcc, brcr, brcc);
  hillary->write_to_file("hw2_out/hillary_fit.raw");
  
  Picture* trump = new Picture("hw2_images/Trump.raw", 512, 512, COLOR_RGB);
  trump->find_hole(&tlcr, &tlcc, &brcr, &brcc);
  trump->fit_piece(Picture("hw2_out/trump_piece_shrink.raw", 100, 100, COLOR_RGB), tlcr, tlcc, brcr, brcc);
  trump->write_to_file("hw2_out/trump_fit.raw");
  
}

void f_puzzle_match(char* piece, int px, int py, char* slot1, int x1, int y1, char* slot2, int x2, int y2, char* out1, char* out2, int mode) {
  Picture* pieces = new Picture(piece, px, py, mode);
  pieces->find_piece("hw2_out/hillary_piece.raw", "hw2_out/trump_piece.raw");
  
  Picture *hillary_piece = new Picture("hw2_out/hillary_piece.raw", 101, 101, mode);
  hillary_piece->crop(0, 0, 99, 99);
  hillary_piece->write_to_file("hw2_out/hillary_piece_shrink.raw");
  
  Picture *trump_piece = new Picture("hw2_out/trump_piece.raw", 101, 101, mode);
  trump_piece->crop(0, 0, 99, 99);
  trump_piece->write_to_file("hw2_out/trump_piece_shrink.raw");
  
  int tlcr; int tlcc;
  int brcr; int brcc;
  
  Picture* hillary = new Picture(slot1, x1, y1, mode);
  hillary->find_hole(&tlcr, &tlcc, &brcr, &brcc);
  hillary->fit_piece(Picture("hw2_out/hillary_piece_shrink.raw", 100, 100, mode), tlcr, tlcc, brcr, brcc);
  hillary->write_to_file(out1);
  
  Picture* trump = new Picture(slot2, x2, y2, mode);
  trump->find_hole(&tlcr, &tlcc, &brcr, &brcc);
  trump->fit_piece(Picture("hw2_out/trump_piece_shrink.raw", 100, 100, mode), tlcr, tlcc, brcr, brcc);
  trump->write_to_file(out2);
}