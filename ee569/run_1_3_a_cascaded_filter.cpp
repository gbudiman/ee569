//
//  run_1_3_a_cascaded_filter.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/7/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Psnr.hpp"
#include "Picture.hpp"
using namespace std;

void f_1_3_a_cascaded_filter() {
  string base = "images/P3/cascaded_filters/";
  string path_lena = base + "Lena.raw";
  string path_lena_noisy = base + "Lena_noisy.raw";
  string path_lena_mean_3 = base + "Lena_mean_3.raw";
  string path_lena_mean_3_mean_3 = base + "Lena_mean_3_mean_3.raw";
  string path_lena_mean_3_mean_3_median_5 = base + "Lena_mean_3_mean_3_median_5.raw";
  string path_lena_mean_3_mean_3_gaussian = base + "Lena_mean_3_mean_3_gaussian.raw";
  string path_lena_mean_7 = base + "Lena_mean_7.raw";
  string path_lena_median_3 = base + "Lena_median_3.raw";
  string path_lena_median_3_mean_3 = base + "Lena_median_3_mean_3.raw";
  string path_lena_median_3_mean_3_gaussian_5 = base + "Lena_median_3_mean_3_gaussian_5.raw";
  string path_lena_median_3_mean_3_gaussian_3 = base + "Lena_median_3_mean_3_gaussian_3.raw";
  string path_lena_median_3_mean_5 = base + "Lena_median_3_mean_5.raw";
  string path_lena_median_3_gaussian = base + "Lena_median_3_gaussian.raw";
  string path_lena_median_7 = base + "Lena_median_7.raw";
  string path_lena_gaussian = base + "Lena_gaussian.raw";

  Picture *lena = new Picture(path_lena, 512, 512, COLOR_RGB);
  
  Picture *lena_noisy = new Picture(path_lena_noisy, 512, 512, COLOR_RGB);
  cout << "Base noisy" << endl;
  Psnr(lena, lena_noisy).compute();
  
  cout << "Mean Filter with window size = 3" << endl;
  lena_noisy->apply_mean_filter(3, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  lena_noisy->write_to_file(path_lena_mean_3);
  Picture *lena_mean_3 = new Picture(path_lena_mean_3, 512, 512, COLOR_RGB);
  Psnr(lena, lena_mean_3).compute();
  lena_mean_3->apply_mean_filter(3, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  lena_mean_3->write_to_file(path_lena_mean_3_mean_3);
  Picture *lena_mean_3_mean_3 = new Picture(path_lena_mean_3_mean_3, 512, 512, COLOR_RGB);
  
  cout << "Mean(3) + Mean(3)" << endl;
  Psnr(lena, lena_mean_3_mean_3).compute();
  
  lena_mean_3_mean_3->apply_median_filter(5, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  lena_mean_3_mean_3->write_to_file(path_lena_mean_3_mean_3_median_5);
  Picture *lena_mean_3_mean_3_median_5 = new Picture(path_lena_mean_3_mean_3_median_5, 512, 512, COLOR_RGB);
  
  cout << "Mean(3) + Mean(3) + Median(5)" << endl;
  Psnr(lena, lena_mean_3_mean_3_median_5).compute();
  
  lena_mean_3_mean_3->apply_gaussian_filter(2, 2);
  lena_mean_3_mean_3->write_to_file(path_lena_mean_3_mean_3_gaussian);
  Picture *lena_mean_3_mean_3_gaussian = new Picture(path_lena_mean_3_mean_3_gaussian, 512, 512, COLOR_RGB);
  cout << "Mean(3) + Mean(3) + Gaussian" << endl;
  Psnr(lena, lena_mean_3_mean_3_gaussian).compute();
  
  cout << "Mean Filter with window size = 7" << endl;
  lena_noisy->apply_mean_filter(7, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  lena_noisy->write_to_file(path_lena_mean_7);
  Picture *lena_mean_7 = new Picture(path_lena_mean_7, 512, 512, COLOR_RGB);
  Psnr(lena, lena_mean_7).compute();
  
  cout << "Median Filter with window size = 3" << endl;
  lena_noisy->apply_median_filter(3, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  lena_noisy->write_to_file(path_lena_median_3);
  Picture *lena_median_3 = new Picture(path_lena_median_3, 512, 512, COLOR_RGB);
  Psnr(lena, lena_median_3).compute();
  
  lena_median_3->apply_mean_filter(3, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  lena_median_3->write_to_file(path_lena_median_3_mean_3);
  
  cout << "Median(3) + Mean(3)" << endl;
  Picture *lena_median_3_mean_3 = new Picture(path_lena_median_3_mean_3, 512, 512, COLOR_RGB);
  Psnr(lena, lena_median_3_mean_3).compute();
  
  lena_median_3_mean_3->apply_gaussian_filter(2, 2);
  lena_median_3_mean_3->write_to_file(path_lena_median_3_mean_3_gaussian_5);
  Picture *lena_median_3_mean_3_gaussian_5 = new Picture(path_lena_median_3_mean_3_gaussian_5, 512, 512, COLOR_RGB);
  Psnr(lena, lena_median_3_mean_3_gaussian_5).compute();
  
  lena_median_3_mean_3->apply_gaussian_filter(1, 1);
  lena_median_3_mean_3->write_to_file(path_lena_median_3_mean_3_gaussian_3);
  Picture *lena_median_3_mean_3_gaussian_3 = new Picture(path_lena_median_3_mean_3_gaussian_3, 512, 512, COLOR_RGB);
  Psnr(lena, lena_median_3_mean_3_gaussian_3).compute();
  
  cout << "Median(3) + Mean(5)" << endl;
  lena_median_3->apply_mean_filter(5, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  lena_median_3->write_to_file(path_lena_median_3_mean_5);
  Picture *lena_median_3_mean_5 = new Picture(path_lena_median_3_mean_5, 512, 512, COLOR_RGB);
  Psnr(lena, lena_median_3_mean_5).compute();
  
  cout << "Median(3) + Gaussian(5, 2)" << endl;
  lena_median_3->apply_gaussian_filter(2, 2);
  lena_median_3->write_to_file(path_lena_median_3_gaussian);
  Picture *lena_median_3_gaussian = new Picture(path_lena_median_3_gaussian, 512, 512, COLOR_RGB);
  Psnr(lena, lena_median_3_gaussian).compute();

  cout << "Median Filter with window size = 7" << endl;
  lena_noisy->apply_median_filter(7, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  lena_noisy->write_to_file(path_lena_median_7);
  Picture *lena_median_7 = new Picture(path_lena_median_7, 512, 512, COLOR_RGB);
  Psnr(lena, lena_median_7).compute();
  
  cout << "Gaussian with window size = 5, sigma = 2" << endl;
  lena_noisy->apply_gaussian_filter(2, 2);
  lena_noisy->write_to_file(path_lena_gaussian);
  Picture *lena_gaussian = new Picture(path_lena_gaussian, 512, 512, COLOR_RGB);
  Psnr(lena, lena_gaussian).compute();
}