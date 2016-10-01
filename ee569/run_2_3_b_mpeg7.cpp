//
//  run_2_3_b_mpeg7.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/1/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"

void f_2_3_b_mpeg7() {
  Picture butterfly = Picture("hw2_images/Butterfly.raw", 335, 320, COLOR_BINARY);
  butterfly.copy_data_to_result();
  butterfly.write_to_file("hw2_out/Butterfly_gray.raw");
}
