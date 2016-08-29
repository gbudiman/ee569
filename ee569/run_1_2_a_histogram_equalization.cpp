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
  
  Picture *bd = new Picture(path_bd, 500, 375, COLOR_GRAY);
  Picture *bb = new Picture(path_bb, 500, 375, COLOR_GRAY);
  
  bd->prepare_gnuplot_histogram_data(path_bd, STRIP_EXTENSION);
  bb->prepare_gnuplot_histogram_data(path_bb, STRIP_EXTENSION);
}