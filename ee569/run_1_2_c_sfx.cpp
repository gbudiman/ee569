//
//  run_1_2_c_sfx.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/30/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
#include "Histogram.hpp"
#include "TransferFunction.hpp"
using namespace std;

void f_1_2_c_sfx() {
  string path_1 = "images/P2/Trojan.raw";
  string path_2 = "images/P2/Park.raw";
  string path_1_out = "images/P2/Trojan_sfx.raw";
  string path_2_out = "images/P2/Park_sfx.raw";
  
  Picture *p1 = new Picture(path_1, 450, 300, COLOR_RGB);
  Picture *p2 = new Picture(path_2, 259, 194, COLOR_RGB);
  
  p1->prepare_gnuplot_histogram_data(path_1, STRIP_EXTENSION);
  p2->prepare_gnuplot_histogram_data(path_2, STRIP_EXTENSION);
  
  TransferFunction *tf_red = new TransferFunction();
  TransferFunction *tf_green = new TransferFunction();
  TransferFunction *tf_blue = new TransferFunction();
  
  tf_red->generate_linear(0, 120, 255, 225);
  tf_green->generate_linear(0, 37, 255, 135);
  tf_blue->generate_linear(0, 60, 255, 160);
  
  p1->apply_transfer_function_rgb(tf_red->data, tf_green->data, tf_blue->data);
  p1->prepare_gnuplot_transfer_function(path_1, STRIP_EXTENSION);
  p1->write_to_file(path_1_out);
  
  p2->apply_transfer_function_rgb(tf_red->data, tf_green->data, tf_blue->data);
  p2->prepare_gnuplot_transfer_function(path_2, STRIP_EXTENSION);
  p2->write_to_file(path_2_out);
  
  Picture *p1x = new Picture(path_1_out, 450, 300, COLOR_RGB);
  Picture *p2x = new Picture(path_2_out, 259, 194, COLOR_RGB);
  p1x->prepare_gnuplot_histogram_data(path_1_out, STRIP_EXTENSION);
  p2x->prepare_gnuplot_histogram_data(path_2_out, STRIP_EXTENSION);
}