//
//  run_2_1_a_diamond_warp.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/20/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"

void f_2_1_a_diamond_warp() {
  Picture* kitten = new Picture("hw2_images/Kitten_1.raw", 300, 300, COLOR_RGB);
  kitten->diamond_warp();
}
