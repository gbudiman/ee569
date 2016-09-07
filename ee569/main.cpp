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
  int debug = 10;

  if (RUN_ALL) {
    f_1_1_a_cropping();
    f_1_1_a_resizing();
    f_1_1_b_cmyk();
    f_1_1_b_hsl();
    f_1_2_a_histogram_equalization();
    f_1_2_b_histcolor_equalization();
    f_1_2_c_sfx();
    f_1_2_d_histogram_transform();
    f_1_3_a_median_filtering();
    f_1_3_a_cascaded_filter();
    f_1_3_b_nlm();
  } else {
    switch(debug) {
      case 0: f_1_1_a_cropping(); break;
      case 1: f_1_1_a_resizing(); break;
      case 2: f_1_1_b_cmyk(); break;
      case 3: f_1_1_b_hsl(); break;
      case 4: f_1_2_a_histogram_equalization(); break;
      case 5: f_1_2_b_histcolor_equalization(); break;
      case 6: f_1_2_c_sfx(); break;
      case 7: f_1_2_d_histogram_transform(); break;
      case 8: f_1_3_a_median_filtering(); break;
      case 9: f_1_3_b_nlm(); break;
      case 10: f_1_3_a_cascaded_filter(); break;
    }
  }
  
  
  
  return 0;
}