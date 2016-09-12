//
//  run_1_1_b_cmyk.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
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

void f_cmyk(char* in, int x, int y, int mode, char* out) {
  string path_in = string(in);
  string path_out = string(out);
  
  cout << "Converting " << in << " to CMY channels" << endl;
  Picture *picture_in = new Picture(path_in, x, y, mode);
  picture_in->to_cmyk();
  picture_in->write_to_file(path_out, STRIP_EXTENSION);
}