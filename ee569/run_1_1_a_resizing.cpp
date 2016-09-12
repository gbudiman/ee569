//
//  run_1_1_a_resizing.cpp
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

void f_1_1_a_resizing() {
  string path_anna = "images/P1/Anna_cropped.raw";
  string path_anna_resize_100 = "images/P1/Anna_resize_100.raw";
  string path_anna_resize_200 = "images/P1/Anna_resize_200.raw";
  string path_anna_resize_300 = "images/P1/Anna_resize_300.raw";
  
  string path_rebel = "images/P1/Rebel_cropped_square.raw";
  string path_rebel_resize_100 = "images/P1/Rebel_resize_100.raw";
  string path_rebel_resize_200 = "images/P1/Rebel_resize_200.raw";
  string path_rebel_resize_300 = "images/P1/Rebel_resize_300.raw";
  
  Picture *anna = new Picture(path_anna, 130, 130, COLOR_RGB);
  Picture *rebel = new Picture(path_rebel, 150, 150, COLOR_RGB);
  
  anna->resize(100, 100);
  anna->write_to_file(path_anna_resize_100);
  anna->resize(200, 200);
  anna->write_to_file(path_anna_resize_200);
  anna->resize(300, 300);
  anna->write_to_file(path_anna_resize_300);
  
  rebel->resize(100, 100);
  rebel->write_to_file(path_rebel_resize_100);
  rebel->resize(200, 200);
  rebel->write_to_file(path_rebel_resize_200);
  rebel->resize(300, 300);
  rebel->write_to_file(path_rebel_resize_300);

}

void f_resize(char *in, int x, int y, int mode, char *out, int ox, int oy) {
  string path_in = string(in);
  string path_out = string(out);
  
  printf("Resizing %s to %dx%d\n", in, ox, oy);
  Picture *picture_in = new Picture(path_in, x, y, mode);
  picture_in->resize(ox, oy);
  picture_in->write_to_file(path_out);
}