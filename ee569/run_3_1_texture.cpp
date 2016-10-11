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
#include "Statistics.hpp"

using namespace std;

void process(Picture p) {
  
}

vector<string> expand_filter_names(vector<string> in) {
  vector<string> result = vector<string>();
  for (int i = 0; i < in.size(); i++) {
    for (int j = 0; j < in.size(); j++) {
      result.push_back(in.at(i) + in.at(j));
    }
  }
  
  return result;
}

void f_3_1_texture() {
  Statistics stats = Statistics();
  vector<string> filter_base = { "L5", "E5", "S5", "W5", "R5" };
  vector<string> filter_names = expand_filter_names(filter_base);
  vector<Picture> pictures = vector<Picture>();
  LawsFilter laws_filter = LawsFilter();
  
  for (int i = 1; i <= 12; i++) {
    pictures.push_back(Picture("hw3_images/P1/Texture" + to_string(i) + ".raw", 128, 128, COLOR_GRAY));
  }
  
  int boundary_extension = 2;
  
  for (int i = 0; i < filter_names.size(); i++) {
    printf("  %s  ", filter_names.at(i).c_str());
  }
  printf("\n");
  
  for (int h = 0; h < pictures.size(); h++) {
    process(pictures.at(h));
    pictures.at(h).extend_boundary(boundary_extension);
    pictures.at(h).copy_result_to_data(true);
    pictures.at(h).subtract_average_to_laws_workspace();
    Picture base = pictures.at(h);
    
    vector<float> avgs = vector<float>();
    for (int i = 0; i < laws_filter.filter_banks.size(); i++) {
      Matrix filter = laws_filter.filter_banks.at(i);
      vector<float> unwrapped_filter = filter.unwrap();
      base.apply_laws_filter(unwrapped_filter, boundary_extension);
      float avg = base.average_laws_response(boundary_extension);
      
      avgs.push_back(avg);
      base = pictures.at(h);
    }
    
    for (int i = 0; i < filter_names.size(); i++) {
      printf("%7.1f ", avgs.at(i));
    }
    printf("\n");
    
    stats.add_row(avgs);
  }
  
  stats.compute_column_variance();
  for (int i = 0; i < stats.variance.size(); i++) {
    printf("  ----  ");
  }
  
  printf("\n");
  
  for (int i = 0; i < stats.variance.size(); i++) {
    printf("%7.1f ", stats.variance.at(i));
  }
  
  printf("\n");
}

