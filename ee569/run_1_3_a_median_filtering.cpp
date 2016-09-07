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
  string path_lena_median_denoised = "images/P3/Lena_median_denoised.raw";
  string path_lena_median_denoised_2 = "images/P3/Lena_median_denoised_2.raw";
  string path_lena_gaussian_blur = "images/P3/Lena_gaussian_blur.raw";
  string path_lena_mean_filter = "images/P3/Lena_mean_filter.raw";
  
  Picture *lena = new Picture(path_lena, 512, 512, COLOR_RGB);
  Picture *lena_noisy = new Picture(path_lena_noisy, 512, 512, COLOR_RGB);
  
  lena->prepare_gnuplot_histogram_data(path_lena, STRIP_EXTENSION);
  lena_noisy->prepare_gnuplot_histogram_data(path_lena_noisy, STRIP_EXTENSION);
  
//  lena_noisy->write_separate_rgb_channel(path_lena_noisy);
//  lena_noisy->apply_median_filter(3, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
//  lena_noisy->write_to_file(path_lena_median_denoised);
//  
//  Picture *lena_median_denoised = new Picture(path_lena_median_denoised, 512, 512, COLOR_RGB);
//  lena_median_denoised->prepare_gnuplot_histogram_data(path_lena_median_denoised, STRIP_EXTENSION);
//  lena_median_denoised->apply_median_filter(5, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
//  lena_median_denoised->write_to_file(path_lena_median_denoised_2);
//  
//  Psnr *psnr_lena = new Psnr(lena_noisy, lena);
//  psnr_lena->compute();
//  Psnr *psnr_median = new Psnr(lena_median_denoised, lena);
//  psnr_median->compute();
  
  //lena_noisy->apply_gaussian_filter(3, 0.6f);
  lena_noisy->apply_mean_filter(7, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  lena_noisy->write_to_file(path_lena_mean_filter);
}