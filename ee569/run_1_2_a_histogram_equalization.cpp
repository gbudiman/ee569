//
//  run_1_2_a_histogram_equalization.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/28/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "project_inclusion.hpp"
#include "Picture.hpp"
using namespace std;

void f_1_2_a_histogram_equalization() {
  string path_bd = "images/P2/Beach_dark.raw";
  string path_bb = "images/P2/Beach_bright.raw";
  string path_bd_b = "images/P2/Beach_dark_eqlz_b.raw";
  string path_bb_b = "images/P2/Beach_bright_eqlz_b.raw";
  
  Picture *bd = new Picture(path_bd, 500, 375, COLOR_GRAY);
  Picture *bb = new Picture(path_bb, 500, 375, COLOR_GRAY);
  
  bd->prepare_gnuplot_histogram_data(path_bd, STRIP_EXTENSION);
  bb->prepare_gnuplot_histogram_data(path_bb, STRIP_EXTENSION);
  
  bd->equalize_using_cdf();
  bb->equalize_using_cdf();
  
  bd->write_to_file(path_bd_b);
  bb->write_to_file(path_bb_b);
  
  Picture *bd_b = new Picture(path_bd_b, 500, 375, COLOR_GRAY);
  Picture *bb_b = new Picture(path_bb_b, 500, 375, COLOR_GRAY);
  
  bd_b->prepare_gnuplot_histogram_data(path_bd_b, STRIP_EXTENSION);
  bb_b->prepare_gnuplot_histogram_data(path_bb_b, STRIP_EXTENSION);
}