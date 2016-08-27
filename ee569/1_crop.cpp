//
//  1_crop.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//


#include "main.hpp"
#include "Picture.hpp"
using namespace std;

int main() {
  string path_anna = "images/P1/Anna.raw";

  Picture *anna = new Picture(path_anna, 250, 300, COLOR_RGB);
  anna->write_to_file("images/P1/Anna_circ.raw");
  
  return 0;
}