//
//  run_1_3_b_nlm.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
using namespace std;

void f_1_3_b_nlm() {
  string path_buildings = "images/P3/Buildings_noisy.raw";
  string path_buildings_small = "images/P3/Buildings_small.raw";
  string path_buildings_small_denoise = "images/P3/Buildings_small_denoise.raw";
  
//  Picture *buildings = new Picture(path_buildings, 512, 512, COLOR_RGB);
//  buildings->crop(0,0,63,63);
//  buildings->write_to_file(path_buildings_small);
  
  Picture *buildings_small = new Picture(path_buildings_small, 64, 64, COLOR_RGB);
  buildings_small->apply_nlm_filter(3, 3);
  buildings_small->write_to_file(path_buildings_small_denoise);
}
