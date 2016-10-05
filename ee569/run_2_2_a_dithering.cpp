//
//  run_2_2_a_dithering.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/21/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Picture.hpp"
#include "main.hpp"
using namespace std;

void f_2_2_a_dithering() {
  Picture house = Picture("hw2_images/House.raw", 512, 512, COLOR_GRAY);
  
//  house.dither(DITHER_2);
//  house.write_to_file("hw2_out/House_dither_2.raw");
//  
//  house.dither(DITHER_4);
//  house.write_to_file("hw2_out/House_dither_4.raw");
//  
//  house.dither(DITHER_4A);
//  house.write_to_file("hw2_out/House_dither_4a.raw");
//  
//  house.dither(DITHER_8);
//  house.write_to_file("hw2_out/House_dither_8.raw");
//  
//  house.dither_multi_level(DITHER_2);
//  house.write_to_file("hw2_out/House_dither_2_4.raw");
//  
//  house.dither_multi_level(DITHER_4);
//  house.write_to_file("hw2_out/House_dither_4_4.raw");
//  
//  house.dither_multi_level(DITHER_4A);
//  house.write_to_file("hw2_out/House_dither_4a_4.raw");
//  
//  house.dither_multi_level(DITHER_8);
//  house.write_to_file("hw2_out/House_dither_8_4.raw");
  
  house.dither(DITHER_FSB);
  house.write_to_file("hw2_out/House_fsb.raw");
  
  //house = Picture("hw2_images/House.raw", 512, 512, COLOR_GRAY);
  house.dither(DITHER_JJN);
  house.write_to_file("hw2_out/House_jjn.raw");

  house.dither(DITHER_STUCKI);
  house.write_to_file("hw2_out/House_stucki.raw");
}

void f_dither(char* in, int x, int y, int method, char* out) {
  Picture base = Picture(in, x, y, COLOR_GRAY);
  base.dither(method);
  base.write_to_file(out);
}

void f_dither_multi(char* in, int x, int y, int method, char* out, int level) {
  Picture base = Picture(in, x, y, COLOR_GRAY);
  base.dither_multi_level(method, level);
  base.write_to_file(out);
}
