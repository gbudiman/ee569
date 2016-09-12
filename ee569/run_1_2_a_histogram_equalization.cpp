//
//  run_1_2_a_histogram_equalization.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/28/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "project_inclusion.hpp"
#include "Picture.hpp"
#include "TransferFunction.hpp"
using namespace std;

void f_1_2_a_histogram_equalization() {
  string path_bd = "images/P2/Beach_dark.raw";
  string path_bb = "images/P2/Beach_bright.raw";
  
  string path_bd_a = "images/P2/Beach_dark_eqlz_a.raw";
  string path_bb_a = "images/P2/Beach_bright_eqlz_a.raw";
  
  string path_bd_b = "images/P2/Beach_dark_eqlz_b.raw";
  string path_bb_b = "images/P2/Beach_bright_eqlz_b.raw";
  
  Picture *bd = new Picture(path_bd, 500, 375, COLOR_GRAY);
  Picture *bb = new Picture(path_bb, 500, 375, COLOR_GRAY);
  
  bd->prepare_gnuplot_histogram_data(path_bd, STRIP_EXTENSION);
  bb->prepare_gnuplot_histogram_data(path_bb, STRIP_EXTENSION);
  
  bd->equalize(EQUALIZE_LINEAR);
  bb->equalize(EQUALIZE_LINEAR);
  bd->prepare_gnuplot_transfer_function(path_bd, STRIP_EXTENSION);
  bb->prepare_gnuplot_transfer_function(path_bb, STRIP_EXTENSION);
  bd->write_to_file(path_bd_a);
  bb->write_to_file(path_bb_a);
  
  bd->equalize(EQUALIZE_CDF);
  bb->equalize(EQUALIZE_CDF);
  bd->write_to_file(path_bd_b);
  bb->write_to_file(path_bb_b);
  
  Picture *bd_a = new Picture(path_bd_a, 500, 375, COLOR_GRAY);
  Picture *bd_b = new Picture(path_bd_b, 500, 375, COLOR_GRAY);
  Picture *bb_a = new Picture(path_bb_a, 500, 375, COLOR_GRAY);
  Picture *bb_b = new Picture(path_bb_b, 500, 375, COLOR_GRAY);
  
  bd_a->prepare_gnuplot_histogram_data(path_bd_a, STRIP_EXTENSION);
  bd_b->prepare_gnuplot_histogram_data(path_bd_b, STRIP_EXTENSION);
  bb_a->prepare_gnuplot_histogram_data(path_bb_a, STRIP_EXTENSION);
  bb_b->prepare_gnuplot_histogram_data(path_bb_b, STRIP_EXTENSION);
}

void f_histogram_equalization(char* in, int x, int y, int mode, char* out, int he_mode) {
  string path_in = string(in);
  string path_out = string(out);
  
  printf("Equalizing histogram using method %s\n", he_mode == EQUALIZE_LINEAR ? "linear" : "CDF");
  
  Picture *picture = new Picture(path_in, x, y, mode);
  picture->prepare_gnuplot_histogram_data(path_in, STRIP_EXTENSION);
  picture->equalize(he_mode);
  picture->prepare_gnuplot_transfer_function(path_in, STRIP_EXTENSION);
  picture->write_to_file(path_out);
  
  Picture *result = new Picture(path_out, x, y, mode);
  result->prepare_gnuplot_histogram_data(path_out, STRIP_EXTENSION);
}