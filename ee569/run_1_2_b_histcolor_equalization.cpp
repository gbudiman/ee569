//
//  run_1_2_b_histcolor_equalization.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/28/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "project_inclusion.hpp"
#include "Picture.hpp"
using namespace std;

void f_1_2_b_histcolor_equalization() {
  string path_s = "images/P2/Skyline.raw";
  string path_sza = "images/P2/Skyline_eqlz_a.raw";
  string path_szb = "images/P2/Skyline_eqlz_b.raw";
  
  Picture *s = new Picture(path_s, 600, 400, COLOR_RGB);
  
  s->prepare_gnuplot_histogram_data(path_s, STRIP_EXTENSION);
  
  s->equalize(EQUALIZE_LINEAR);
  s->write_to_file(path_sza);
  
  s->equalize(EQUALIZE_CDF);
  s->write_to_file(path_szb);
  
  Picture *sza = new Picture(path_sza, 600, 400, COLOR_RGB);
  Picture *szb = new Picture(path_szb, 600, 400, COLOR_RGB);
  
  sza->prepare_gnuplot_histogram_data(path_sza, STRIP_EXTENSION);
  szb->prepare_gnuplot_histogram_data(path_szb, STRIP_EXTENSION);
}