//
//  run_1_2_d_histogram_transform.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/29/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
#include "Histogram.hpp"
using namespace std;

void f_1_2_d_histogram_transform() {
  string path_gaussian_1 = "images/P2/gaussian1.txt";
  string path_gaussian_2 = "images/P2/gaussian2.txt";
  string path_s1 = "images/P2/Student_1.raw";
  string path_s2 = "images/P2/Student_2.raw";
  string path_s1m = "images/P2/Student_1_matched.raw";
  string path_s2m = "images/P2/Student_2_matched.raw";
  Histogram *h1 = new Histogram();
  Histogram *h2 = new Histogram();
  h1->generate_gaussian(125, 40, 500, 332);
  h2->generate_gaussian(125, 40, 500, 375);
 
  Picture *pseudo1 = new Picture();
  Picture *pseudo2 = new Picture();
  Picture *s1 = new Picture(path_s1, 500, 332, COLOR_GRAY);
  Picture *s2 = new Picture(path_s2, 500, 375, COLOR_GRAY);
  
  pseudo1->assign_histogram(h1, CHANNEL_GRAY, 500, 332);
  pseudo1->prepare_gnuplot_histogram_data(path_gaussian_1, STRIP_EXTENSION);
  pseudo1->equalize(EQUALIZE_CDF);

  pseudo2->assign_histogram(h2, CHANNEL_GRAY, 500, 375);
  pseudo2->prepare_gnuplot_histogram_data(path_gaussian_2, STRIP_EXTENSION);
  pseudo2->equalize(EQUALIZE_CDF);
  
  s1->prepare_gnuplot_histogram_data(path_s1, STRIP_EXTENSION);
  s2->prepare_gnuplot_histogram_data(path_s2, STRIP_EXTENSION);
  s1->equalize(EQUALIZE_CDF);
  s2->equalize(EQUALIZE_CDF);
  
  s1->histogram_match_gray(pseudo1->cdf_gray);
  s1->write_to_file(path_s1m);
  s2->histogram_match_gray(pseudo2->cdf_gray);
  s2->write_to_file(path_s2m);
  
  Picture *s1m = new Picture(path_s1m, 500, 332, COLOR_GRAY);
  s1m->prepare_gnuplot_histogram_data(path_s1m, STRIP_EXTENSION);
  
  Picture *s2m = new Picture(path_s2m, 500, 375, COLOR_GRAY);
  s2m->prepare_gnuplot_histogram_data(path_s2m, STRIP_EXTENSION);
}