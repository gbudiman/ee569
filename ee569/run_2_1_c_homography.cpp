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
  Picture field = Picture("hw2_images/field.raw", 972, 648, COLOR_RGB);
  
  field.overlay_with(trojan);
  field.write_to_file("hw2_out/trojans_field.raw");
}
