//
//  run_1_3_a_median_filtering.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
#include "Histogram.hpp"
#include "Psnr.hpp"
using namespace std;

void f_1_3_a_median_filtering() {
  string path_lena = "images/P3/Lena.raw";
  string path_lena_noisy = "images/P3/Lena_noisy.raw";
  
  Picture *lena = new Picture(path_lena, 512, 512, COLOR_RGB);
  Picture *lena_noisy = new Picture(path_lena_noisy, 512, 512, COLOR_RGB);
  
  lena->prepare_gnuplot_histogram_data(path_lena, STRIP_EXTENSION);
  lena_noisy->prepare_gnuplot_histogram_data(path_lena_noisy, STRIP_EXTENSION);
  
  Psnr *psnr_auto = new Psnr(lena, lena);
  Psnr *psnr_lena = new Psnr(lena, lena_noisy);
  psnr_auto->compute();
  psnr_lena->compute();
}