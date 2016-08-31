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
  string path_1_match = "images/P2/Trojan_match.raw";
  string path_2_match = "images/P2/Park_match.raw";
  string path_1_out = "images/P2/Trojan_sfx.raw";
  string path_2_out = "images/P2/Park_sfx.raw";
  string path_ref = "images/P2/Skyline.raw";
  
  Picture *ref = new Picture(path_ref, 600, 400, COLOR_RGB);
  Picture *p1 = new Picture(path_1, 450, 300, COLOR_RGB);
  Picture *p2 = new Picture(path_2, 259, 194, COLOR_RGB);
  
  p1->prepare_gnuplot_histogram_data(path_1, STRIP_EXTENSION);
  p2->prepare_gnuplot_histogram_data(path_2, STRIP_EXTENSION);
  
  // Method B
  Picture *pseudo1 = new Picture();
  Picture *pseudo2 = new Picture();
  Histogram *ref_r = ref->hist_r;
  Histogram *ref_g = ref->hist_g;
  Histogram *ref_b = ref->hist_b;
  
  float scaling_factor = (float) (450 * 300) / (float) (600 * 400);
  ref_r->rescale(scaling_factor);
  ref_g->rescale(scaling_factor);
  ref_b->rescale(scaling_factor);
  pseudo1->assign_histogram(ref_r, CHANNEL_RED, 450, 300);
  pseudo1->assign_histogram(ref_g, CHANNEL_GREEN, 450, 300);
  pseudo1->assign_histogram(ref_b, CHANNEL_BLUE, 450, 300);
  pseudo1->equalize(EQUALIZE_CDF);
  
  p1->equalize(EQUALIZE_CDF);
  p1->histogram_match_rgb(pseudo1->cdf_r, pseudo1->cdf_g, pseudo1->cdf_b);
  p1->write_to_file(path_1_match);
  
  ref = new Picture(path_ref, 600, 400, COLOR_RGB);
  scaling_factor = (float) (259 * 194) / (float) (600 * 400);
  ref_r = ref->hist_r;
  ref_g = ref->hist_g;
  ref_b = ref->hist_b;
  ref_r->rescale(scaling_factor);
  ref_g->rescale(scaling_factor);
  ref_b->rescale(scaling_factor);
  pseudo2->assign_histogram(ref_r, CHANNEL_RED, 259, 194);
  pseudo2->assign_histogram(ref_g, CHANNEL_GREEN, 259, 194);
  pseudo2->assign_histogram(ref_b, CHANNEL_BLUE, 259, 194);
  pseudo2->equalize(EQUALIZE_CDF);
  
  p2->equalize(EQUALIZE_CDF);
  p2->histogram_match_rgb(pseudo2->cdf_r, pseudo2->cdf_g, pseudo2->cdf_b);
  p2->write_to_file(path_2_match);
  
  Picture *p1m = new Picture(path_1_match, 450, 300, COLOR_RGB);
  Picture *p2m = new Picture(path_2_match, 259, 194, COLOR_RGB);
  p1m->prepare_gnuplot_histogram_data(path_1_match, STRIP_EXTENSION);
  p2m->prepare_gnuplot_histogram_data(path_2_match, STRIP_EXTENSION);
  // Method B
  
  // Method A
  p1 = new Picture(path_1, 450, 300, COLOR_RGB);
  p2 = new Picture(path_2, 259, 194, COLOR_RGB);
  
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