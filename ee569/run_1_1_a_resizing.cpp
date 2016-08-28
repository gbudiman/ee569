//
//  run_1_1_a_resizing.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "project_inclusion.hpp"
#include "Picture.hpp"
using namespace std;

void f_1_1_a_resizing() {
  string path_anna = "images/P1/Anna_cropped.raw";
  string path_anna_resize_100 = "images/P1/Anna_resize_100.raw";
  string path_anna_resize_200 = "images/P1/Anna_resize_200.raw";
  string path_anna_resize_300 = "images/P1/Anna_resize_300.raw";
  
  Picture *anna = new Picture(path_anna, 130, 130, COLOR_RGB);
  anna->resize(100, 100);
  anna->write_to_file(path_anna_resize_100);
  anna->resize(200, 200);
  anna->write_to_file(path_anna_resize_200);
  anna->resize(300, 300);
  anna->write_to_file(path_anna_resize_300);
}