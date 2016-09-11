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

int main(int argc, char* argv[]) {
  int debug = -1;

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
      case 11: f_1_3_b_cascaded_filter(); break;
      case 12: f_1_3_psnr_calculator(); break;
    }
  }

  if (xcmp(argv[1], "crop")) {
    int x, y, mode, x1, y1, x2, y2;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    sscanf(argv[7], "%d", &x1);
    sscanf(argv[8], "%d", &y1);
    sscanf(argv[9], "%d", &x2);
    sscanf(argv[10], "%d", &y2);
    f_crop(argv[2], x, y, mode, argv[6], x1, y1, x2, y2);
  } else if (xcmp(argv[1], "resize")) {
    int x, y, mode, ox, oy;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    sscanf(argv[7], "%d", &ox);
    sscanf(argv[8], "%d", &oy);
    f_resize(argv[2], x, y, mode, argv[6], ox, oy);
  } else if (xcmp(argv[1], "rgb2cmy")) {
    int x, y, mode;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    f_cmyk(argv[2], x, y, mode, argv[6]);
  } else if (xcmp(argv[1], "rgb2hsl")) {
    int x, y, mode;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    f_hsl(argv[2], x, y, mode, argv[6]);
  } else if (xcmp(argv[1], "hist_equalize_linear")) {
    int x, y, mode;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    f_histogram_equalization(argv[2], x, y, mode, argv[6], EQUALIZE_LINEAR);
  } else if (xcmp(argv[1], "hist_equalize_cdf")) {
    int x, y, mode;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    f_histogram_equalization(argv[2], x, y, mode, argv[6], EQUALIZE_CDF);
  } else if (xcmp(argv[1], "sfx")) {
    int ix, iy, rx, ry;
    sscanf(argv[3], "%d", &ix);
    sscanf(argv[4], "%d", &iy);
    sscanf(argv[6], "%d", &rx);
    sscanf(argv[7], "%d", &ry);
    f_sfx(argv[2], ix, iy, argv[5], rx, ry, argv[8]);
  } else if (xcmp(argv[1], "hist_match")) {
    int x, y, mode, mean, dist;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    sscanf(argv[7], "%d", &mean);
    sscanf(argv[8], "%d", &dist);
    f_hist_match(argv[2], x, y, mode, argv[6], mean, dist);
  }
  
  return 0;
}

bool xcmp(char* a, const char* b) {
  return (strcmp(a, b) == 0);
}