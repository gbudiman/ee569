//
//  run_2_1_c_homography.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/26/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
using namespace std;

void f_2_1_c_homography() {
  Picture trojan = Picture("hw2_images/trojans.raw", 350, 146, COLOR_RGB);
  Picture tartan = Picture("hw2_images/tartans.raw", 350, 146, COLOR_RGB);
  Picture field = Picture("hw2_images/field.raw", 972, 648, COLOR_RGB);
  
  field.overlay_with(trojan);
  field.write_to_file("hw2_out/trojans_field.raw");
  
  field.overlay_with(tartan);
  field.write_to_file("hw2_out/tartan_field.raw");
}

void f_homography(char* in, int ix, int iy, char* ov, int ox, int oy, char* out, int mode) {
  Picture base = Picture(in, ix, iy, mode);
  Picture overlay = Picture(ov, ox, oy, mode);
  base.overlay_with(overlay);
  base.write_to_file(out);
}