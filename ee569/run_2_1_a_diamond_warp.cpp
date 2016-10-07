//
//  run_2_1_a_diamond_warp.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/20/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"

void f_2_1_a_diamond_warp() {
  Picture* kitten = new Picture("hw2_images/Kitten_1.raw", 300, 300, COLOR_RGB);
  kitten->diamond_warp();
  kitten->write_to_file("hw2_out/Kitten_1_warped.raw");
  
  kitten = new Picture("hw2_images/Kitten_2.raw", 300, 300, COLOR_RGB);
  kitten->diamond_warp();
  kitten->write_to_file("hw2_out/Kitten_2_warped.raw");
}

void f_diamond_warp(char *in, char *out, int x, int y, int mode) {
  Picture* p = new Picture(in, x, y, mode);
  p->diamond_warp();
  p->write_to_file(out);
}