//
//  run_1_3_b_nlm.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
#include "Psnr.hpp"
using namespace std;

void f_1_3_b_nlm() {
  string path_lena_ref = "images/P3/Lena.raw";
  string path_lena = "images/P3/Lena_noisy.raw";
  string path_lena_step1 = "images/P3/Lena_step1.raw";
  string path_lena_step2 = "images/P3/Lena_step2.raw";
  string path_lena_nlm_7_3 = "images/P3/Lena_nlm_7_3.raw";
  string path_lena_nlm_15_3 = "images/P3/Lena_nlm_15_3.raw";
  string path_lena_nlm_21_3 = "images/P3/Lena_nlm_21_3.raw";
  string path_lena_nlm_7_5 = "images/P3/Lena_nlm_7_5.raw";
  string path_lena_nlm_15_5 = "images/P3/Lena_nlm_15_5.raw";
  string path_lena_nlm_21_5 = "images/P3/Lena_nlm_21_5.raw";
  string path_lena_denoise = "images/P3/Lena_denoise_nlm.raw";
  string path_buildings_ref = "images/P3/Buildings.raw";
  string path_buildings = "images/P3/Buildings_noisy.raw";
  string path_buildings_denoise = "images/P3/Buildings_denoise.raw";
  string path_buildings_small_0 = "images/P3/Buildings_small_0.raw";
  string path_buildings_small_1 = "images/P3/Buildings_small_1.raw";
  string path_buildings_small_denoise_0 = "images/P3/Buildings_small_denoise_0.raw";
  string path_buildings_small_denoise_1 = "images/P3/Buildings_small_denoise_1.raw";
  string path_trees_ref = "images/P3/Trees.raw";
  string path_trees = "images/P3/Trees_noisy.raw";
  string path_trees_small = "images/P3/Trees_small.raw";
  string path_trees_small_denoise = "images/P3/Trees_small_denoise.raw";
  string path_trees_denoise = "images/P3/Trees_denoise.raw";
  
//  Picture *lena_ref = new Picture(path_lena_ref, 512, 512, COLOR_RGB);
//  Picture *lena_denoised = new Picture(path_lena_denoise, 512, 512, COLOR_RGB);
//  Picture *lena = new Picture(path_lena, 512, 512, COLOR_RGB);
//  
//  cout << "Lena" << endl;
//  //Psnr(lena_ref, lena_denoised).compute();
//  //Psnr(lena_ref, lena).compute();
//  lena->apply_median_filter(3, FILTER_RED | FILTER_GREEN | FILTER_BLUE);
//  lena->write_to_file(path_lena_step1);
//  
//  Picture *lena_step1 = new Picture(path_lena_step1, 512, 512, COLOR_RGB);
//  lena_step1->apply_mean_filter(3, FILTER_RED | FILTER_GREEN | FILTER_BLUE);
//  lena->write_to_file(path_lena_step2);
//  
//  Picture *lena_step2 = new Picture(path_lena_step2, 512, 512, COLOR_RGB);
//  lena_step2->apply_nlm_filter(7, 5);
//  lena_step2->write_to_file(path_lena_nlm_7_5);
//  
//  lena_step2->apply_nlm_filter(15, 5);
//  lena_step2->write_to_file(path_lena_nlm_15_5);
//  
//  lena_step2->apply_nlm_filter(21, 5);
//  lena_step2->write_to_file(path_lena_nlm_21_5);
  
  //lena->apply_nlm_filter(NLM_SEARCH_RADIUS, NLM_PATCH_RADIUS);
  //lena->write_to_file(path_lena_denoise);
  
  
//  lena->apply_nlm_filter(17, 3);
//  lena->write_to_file(path_lena_denoise);
  
//
//  Picture *buildings = new Picture(path_buildings, 512, 512, COLOR_RGB);
//  buildings->crop(0, 0, 63, 63);
//  buildings->write_to_file(path_buildings_small_0);
//  buildings->crop(96, 96, 159, 159);
//  buildings->write_to_file(path_buildings_small_1);
//  
//  Picture *buildings_small_0 = new Picture(path_buildings_small_0, 64, 64, COLOR_RGB);
//  buildings_small_0->apply_nlm_filter(7, 3);
//  buildings_small_0->write_to_file(path_buildings_small_denoise_0);
////
//  Picture *buildings_small_1 = new Picture(path_buildings_small_1, 64, 64, COLOR_RGB);
//  buildings_small_1->apply_nlm_filter(7, 3);
//  buildings_small_1->write_to_file(path_buildings_small_denoise_1);
  
//  Picture *buildings_ref = new Picture(path_buildings_ref, 512, 512, COLOR_RGB);
//  Picture *buildings_denoised = new Picture(path_buildings_denoise, 512, 512, COLOR_RGB);
//  Picture *buildings = new Picture(path_buildings, 512, 512, COLOR_RGB);
  
  //cout << "Buildings" << endl;
  //Psnr(buildings_ref, buildings_denoised).compute();
  //Psnr(buildings_ref, buildings).compute();
//  buildings->apply_nlm_filter(NLM_SEARCH_RADIUS, NLM_PATCH_RADIUS);
//  buildings->write_to_file(path_buildings_denoise);
  
//  buildings->apply_nlm_filter(10, 3);
//  buildings->write_to_file(path_buildings_denoise);
  
  Picture *trees = new Picture(path_trees, 774, 518, COLOR_RGB);
//  trees->crop(128,128,191,191);
//  trees->write_to_file(path_trees_small);
//  
//  Picture *trees_small = new Picture(path_trees_small, 64, 64, COLOR_RGB);
//  trees_small->apply_nlm_filter(17, 3);
//  trees_small->write_to_file(path_trees_small_denoise);
  
//  Picture *trees_ref = new Picture(path_trees_ref, 774, 518, COLOR_RGB);
//  Picture *trees_denoised = new Picture(path_trees_denoise, 774, 518, COLOR_RGB);
//  Picture *trees = new Picture(path_trees, 774, 518, COLOR_RGB);
  
//  cout << "Trees" << endl;
  //Psnr(trees_ref, trees_denoised).compute();
  //Psnr(trees_ref, trees).compute();
  trees->apply_nlm_filter(NLM_SEARCH_RADIUS, NLM_PATCH_RADIUS);
  trees->write_to_file(path_trees_denoise);
//  trees->apply_nlm_filter(17, 3);
//  trees->write_to_file(path_trees_denoise);
}
