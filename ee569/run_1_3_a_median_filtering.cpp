//
//  run_1_3_a_median_filtering.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
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

void f_denoise_mean(char *in, int x, int y, int mode, char *out, int window_size) {
  string path_in = string(in);
  string path_out = string(out);
  
  printf("Denoising using mean filter with window size %dx%d\n", window_size, window_size);
  Picture *picture = new Picture(path_in, x, y, mode);
  picture->apply_mean_filter(window_size, FILTER_RED | FILTER_GREEN | FILTER_BLUE);
  picture->write_to_file(path_out);
}

void f_denoise_median(char *in, int x, int y, int mode, char *out, int window_size) {
  string path_in = string(in);
  string path_out = string(out);
  
  printf("Denoising using median filter with window size %dx%d\n", window_size, window_size);
  Picture *picture = new Picture(path_in, x, y, mode);
  picture->apply_median_filter(window_size, FILTER_RED | FILTER_GREEN | FILTER_BLUE);
  picture->write_to_file(path_out);
}

void f_denoise_gaussian(char *in, int x, int y, int mode, char *out, int radius, float factor) {
  string path_in = string(in);
  string path_out = string(out);
  
  printf("Denoising using gaussian filter with window size %dx%d and decay factor of %f\n", radius * 2 + 1, radius * 2 + 1, factor);
  
  Picture *picture = new Picture(path_in, x, y, mode);
  picture->apply_gaussian_filter(radius, factor);
  picture->write_to_file(path_out);
}

void f_denoise_nlm(char *in, int x, int y, int mode, char *out, int search_radius, int window_radius, float factor) {
  string path_in = string(in);
  string path_out = string(out);
  
  printf("Denoising using NLM filter with search_radius = %d, window_radius = %d, and decay_factor = %f\n", search_radius, window_radius, factor);
  Picture *picture = new Picture(path_in, x, y, mode);
  picture->apply_nlm_filter(search_radius, window_radius, factor);
  picture->write_to_file(path_out);
}

void f_psnr(char *a, char *b, int x, int y, int mode) {
  cout << "Comparing " << a << " against " << b << endl;
  Picture *picture_a = new Picture(string(a), x, y, mode);
  Picture *picture_b = new Picture(string(b), x, y, mode);
  Psnr(picture_a, picture_b).compute();
}