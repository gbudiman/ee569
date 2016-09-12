//
//  run_1_1_b_hsl.cpp
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

void f_1_1_b_hsl() {
  string path_turtle = "images/P1/Turtle.raw";
  string path_jellyfish = "images/P1/Jellyfish.raw";
  
  Picture *turtle = new Picture(path_turtle, 400, 250, COLOR_RGB);
  Picture *jellyfish = new Picture(path_jellyfish, 500, 333, COLOR_RGB);
  
  turtle->to_hsl();
  turtle->write_to_file(path_turtle, STRIP_EXTENSION);
  
  jellyfish->to_hsl();
  jellyfish->write_to_file(path_jellyfish, STRIP_EXTENSION);
}

void f_hsl(char* in, int x, int y, int mode, char* out) {
  string path_in = string(in);
  string path_out = string(out);
  
  cout << "Converting " << in << " to HSL channels" << endl;
  Picture *picture_in = new Picture(path_in, x, y, mode);
  picture_in->to_hsl();
  picture_in->write_to_file(path_out, STRIP_EXTENSION);
}