//
//  run_1_1_a_cropping.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "project_inclusion.hpp"
#include "Picture.hpp"
using namespace std;

void f_1_1_a_cropping() {
  string path_anna = "images/P1/Anna.raw";
  string path_anna_out_square = "images/P1/Anna_cropped_square.raw";
  string path_anna_out_rect = "images/P1/Anna_cropped_rect.raw";
  string path_rebel = "images/P1/Rebel.raw";
  string path_rebel_out_square = "images/P1/Rebel_cropped_square.raw";
  string path_rebel_out_rect = "images/P1/Rebel_cropped_rect.raw";
  
  Picture *anna = new Picture(path_anna, 250, 300, COLOR_RGB);
  Picture *rebel = new Picture(path_rebel, 200, 300, COLOR_RGB);
  
  anna->crop(55, 85, 184, 214); // 130x130
  anna->write_to_file(path_anna_out_square);
  anna->crop(55, 30, 184, 239); // 130x210
  anna->write_to_file(path_anna_out_rect);
  
  rebel->crop(25, 25, 174, 174); // 150x150
  rebel->write_to_file(path_rebel_out_square);
  rebel->crop(35, 20, 164, 199); // 130x180
  rebel->write_to_file(path_rebel_out_rect);
}