//
//  run_1_3_psnr_calculator.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/9/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Psnr.hpp"
using namespace std;

string wrap_base(string x) {
  return "images/P3/" + x + ".raw";
}

Picture* we_lena(int search_radius, int window_radius, string decay_factor) {
  return new Picture("images/P3/experiments_"
                     + to_string(search_radius) + "_"
                     + to_string(window_radius) + "_"
                     + decay_factor + "/Lena_denoise_nlm.raw", 512, 512, COLOR_RGB);
}

Picture* we_bld(int search_radius, int window_radius, string decay_factor) {
  return new Picture("images/P3/experiments_"
                     + to_string(search_radius) + "_"
                     + to_string(window_radius) + "_"
                     + decay_factor + "/Buildings_denoise.raw", 512, 512, COLOR_RGB);
}

Picture* we_trees(int search_radius, int window_radius, string decay_factor) {
  return new Picture("images/P3/experiments_"
                     + to_string(search_radius) + "_"
                     + to_string(window_radius) + "_"
                     + decay_factor + "/Trees_denoise.raw", 774, 518, COLOR_RGB);
}

Picture* st_lena(int search_radius, int window_radius, string decay_factor) {
  return new Picture("images/P3/lena_stack_" + decay_factor + "/"
                     + "Lena_nlm_"
                     + to_string(search_radius) + "_"
                     + to_string(window_radius) + ".raw", 512, 512, COLOR_RGB);
}

void f_1_3_psnr_calculator() {
  Picture* lena = new Picture(wrap_base("Lena"), 512, 512, COLOR_RGB);
  Picture* lena_noisy = new Picture("images/P3/Lena_noisy.raw", 512, 512, COLOR_RGB);
  Picture* buildings = new Picture(wrap_base("Buildings"), 512, 512, COLOR_RGB);
  Picture* buildings_noisy = new Picture("images/P3/Buildings_noisy.raw", 512, 512, COLOR_RGB);
  Picture* trees = new Picture(wrap_base("Trees"), 774, 518, COLOR_RGB);
  Picture* trees_noisy = new Picture("images/P3/Trees_noisy.raw", 774, 518, COLOR_RGB);
  
  Psnr(lena, lena_noisy).compute();
  cout << "--\n";
  Psnr(lena, we_lena(7,1,"0.001")).compute();
  Psnr(lena, we_lena(7,3,"0.01")).compute();
  Psnr(lena, we_lena(7,3,"0.001")).compute();
  Psnr(lena, we_lena(7,3,"0.0001")).compute();
  Psnr(lena, we_lena(7,5,"0.0025")).compute();
  Psnr(lena, we_lena(15,1,"0.001")).compute();
  Psnr(lena, we_lena(15,3,"0.001")).compute();
  Psnr(lena, we_lena(15,3,"0.005")).compute();
  Psnr(lena, we_lena(15,3,"0.0025")).compute();
  Psnr(lena, we_lena(15,5,"0.0025")).compute();
  Psnr(lena, we_lena(21,3,"0.0025")).compute();
  Psnr(lena, we_lena(21,5,"0.0025")).compute();
  Psnr(lena, we_lena(21,7,"0.001")).compute();
  cout << "---\n";
  Psnr(lena, st_lena(7,3,"0.001")).compute();
  Psnr(lena, st_lena(7,5,"0.001")).compute();
  Psnr(lena, st_lena(15,3,"0.001")).compute();
  Psnr(lena, st_lena(15,5,"0.001")).compute();
  Psnr(lena, st_lena(21,3,"0.001")).compute();
  Psnr(lena, st_lena(21,5,"0.001")).compute();
  Psnr(lena, st_lena(7,3,"0.005")).compute();
  Psnr(lena, st_lena(15,3,"0.005")).compute();
  Psnr(lena, st_lena(21,3,"0.005")).compute();
  Psnr(lena, st_lena(7,3,"0.0025")).compute();
  Psnr(lena, st_lena(15,3,"0.0025")).compute();
  Psnr(lena, st_lena(21,3,"0.0025")).compute();
  cout << "Buildings\n";
  Psnr(buildings, buildings_noisy).compute();
  cout << "--\n";
  Psnr(buildings, we_bld(7,1,"0.001")).compute();
  Psnr(buildings, we_bld(7,3,"0.01")).compute();
  Psnr(buildings, we_bld(7,3,"0.001")).compute();
  Psnr(buildings, we_bld(7,3,"0.0001")).compute();
  Psnr(buildings, we_bld(7,5,"0.0025")).compute();
  Psnr(buildings, we_bld(15,1,"0.001")).compute();
  Psnr(buildings, we_bld(15,3,"0.001")).compute();
  Psnr(buildings, we_bld(15,3,"0.005")).compute();
  Psnr(buildings, we_bld(15,3,"0.0025")).compute();
  Psnr(buildings, we_bld(15,5,"0.0025")).compute();
  Psnr(buildings, we_bld(21,3,"0.0025")).compute();
  Psnr(buildings, we_bld(21,5,"0.0025")).compute();
  Psnr(buildings, we_bld(21,7,"0.001")).compute();
  cout << "Trees\n";
  Psnr(trees, trees_noisy).compute();
  cout << "--\n";
  Psnr(trees, we_trees(7,1,"0.001")).compute();
  Psnr(trees, we_trees(7,3,"0.01")).compute();
  Psnr(trees, we_trees(7,3,"0.001")).compute();
  Psnr(trees, we_trees(7,3,"0.0001")).compute();
  Psnr(trees, we_trees(7,5,"0.0025")).compute();
  Psnr(trees, we_trees(15,1,"0.001")).compute();
  Psnr(trees, we_trees(15,3,"0.001")).compute();
  Psnr(trees, we_trees(15,3,"0.005")).compute();
  //Psnr(trees, we_trees(15,3,"0.0025")).compute();
  Psnr(trees, we_trees(15,5,"0.0025")).compute();
  Psnr(trees, we_trees(21,3,"0.0025")).compute();
  Psnr(trees, we_trees(21,5,"0.0025")).compute();
  Psnr(trees, we_trees(21,7,"0.001")).compute();
}

