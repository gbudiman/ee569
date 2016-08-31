//
//  main.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "project_inclusion.hpp"
using namespace std;

int main() {
  int debug = 6;

  switch(debug) {
    case 0: f_1_1_a_cropping(); break;
    case 1: f_1_1_a_resizing(); break;
    case 2: f_1_1_b_cmyk(); break;
    case 3: f_1_1_b_hsl(); break;
    case 4: f_1_2_a_histogram_equalization(); break;
    case 5: f_1_2_b_histcolor_equalization(); break;
    case 6: f_1_2_c_sfx(); break;
    case 7: f_1_2_d_histogram_transform(); break;
  }
  
  return 0;
}