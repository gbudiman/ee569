//
//  run_3_1_segmentation.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/12/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
#include "LawsFilter.hpp"
#include "FilterEnergy.hpp"
using namespace std;
using namespace cv;

void f_3_1_segmentation() {
  FilterEnergy filter_energy = FilterEnergy();
  vector<string> filter_base = { "L5", "E5", "S5", "W5", "R5" };
  vector<string> filter_names = expand_filter_names(filter_base);
  Mat m = Mat::zeros(500*425, 25, CV_8UC1);
  
  int boundary_extension = 2;
  LawsFilter laws_filter = LawsFilter();
  Picture comb1 = Picture("hw3_images/P1/Comb_1.raw", 500, 425, COLOR_GRAY);
  
  comb1.extend_boundary(boundary_extension);
  comb1.copy_result_to_data(true);
  comb1.subtract_average_to_laws_workspace();
  
  for (int i = 0; i < laws_filter.filter_banks.size(); i++) {
    Matrix filter = laws_filter.filter_banks.at(i);
    vector<float> unwrapped_filter = filter.unwrap();
    comb1.apply_laws_filter(unwrapped_filter, boundary_extension);
    
    float avg = comb1.average_laws_response(boundary_extension);
    printf("%7.2f\n", avg);
    
    comb1.normalize_laws_filter_response(boundary_extension);
    comb1.write_to_file("hw3_out/P1_comb1_responses/resp_" + filter_names.at(i) + ".raw");
    filter_energy.add(comb1.window_laws_response(7));
    
    int z = 0;
  }
  
  filter_energy.normalize();
}