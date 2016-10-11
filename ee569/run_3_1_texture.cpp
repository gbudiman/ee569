//
//  run_3_1_texture.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/10/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
#include "LawsFilter.hpp"
using namespace std;

void process(Picture p) {
  
}

void f_3_1_texture() {
  vector<Picture> pictures = vector<Picture>();
  LawsFilter laws_filter = LawsFilter();
  
  pictures.push_back(Picture("hw3_images/P1/Texture1.raw", 128, 128, COLOR_GRAY));
  
  for (int i = 0; i < pictures.size(); i++) {
    process(pictures.at(i));
    pictures.at(i).extend_boundary(2);
    pictures.at(i).write_to_file("hw3_out/P1/Texture1_extended.raw");
  }
  
  
}

