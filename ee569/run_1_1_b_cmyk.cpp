//
//  run_1_1_b_cmyk.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "project_inclusion.hpp"
#include "Picture.hpp"
using namespace std;

void f_1_1_b_cmyk() {
  string path_fish = "images/P1/Clownfish.raw";
  string path_octopus = "images/P1/Octopus.raw";
  
  Picture *fish = new Picture(path_fish, 600, 400, COLOR_RGB);
  Picture *octopus = new Picture(path_octopus, 500, 374, COLOR_RGB);
  
  fish->to_cmyk();
  fish->write_to_file(path_fish, STRIP_EXTENSION);
  
  octopus->to_cmyk();
  octopus->write_to_file(path_octopus, STRIP_EXTENSION);
}