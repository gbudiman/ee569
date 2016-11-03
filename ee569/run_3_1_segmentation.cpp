//
//  run_3_1_segmentation.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/12/16.
//  Finalized on 10/31/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
#include "LawsFilter.hpp"
#include "FilterEnergy.hpp"
using namespace std;
using namespace cv;

bool is_in_vector(vector<int> v, int val) {
  return find(v.begin(), v.end(), val) != v.end();
}

void f_3_1_segmentation() {
  bool enable_advanced = true;
  Mat wrapped_kmeans, centers;
  Picture leveled("", 0, 0, COLOR_RGB);
  
  FilterEnergy filter_energy = FilterEnergy();
  vector<string> filter_base = { "L5", "E5", "S5", "W5", "R5" };
  //vector<int> comb2_selected = {0, 1, 5, 6, 7, 10, 11, 12, 23};
  vector<int> comb2_selected = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
  vector<string> filter_names = expand_filter_names(filter_base);
  Mat m = Mat::zeros(500*425, 25, CV_8UC1);
  
  int boundary_extension = 2;
  LawsFilter laws_filter = LawsFilter();
//  Picture comb1 = Picture("hw3_images/P1/Comb_1.raw", 500, 425, COLOR_GRAY);
//  
//  comb1.extend_boundary(boundary_extension);
//  comb1.copy_result_to_data(true);
//  comb1.subtract_average_to_laws_workspace();
//  
//  for (int i = 0; i < laws_filter.filter_banks.size(); i++) {
//    Matrix filter = laws_filter.filter_banks.at(i);
//    vector<float> unwrapped_filter = filter.unwrap();
//    comb1.apply_laws_filter(unwrapped_filter, boundary_extension);
//    
//    float avg = comb1.average_laws_response(boundary_extension);
//    printf("%7.2f\n", avg);
//    
//    comb1.normalize_laws_filter_response(boundary_extension);
//    comb1.copy_result_to_data();
//    comb1.crop(2, 2, 501, 426);
//    comb1.write_to_file("hw3_out/P1_comb1_responses/resp_" + filter_names.at(i) + ".raw");
//    Picture s_resp = Picture("hw3_out/P1_comb1_responses/resp_" + filter_names.at(i) + ".raw", 500, 425, COLOR_GRAY);
//    s_resp.copy_data_to_result();
//    vector<vector<float>> energy = s_resp.window_laws_response(100);
//    filter_energy.add(energy);
//    s_resp.slurp(energy);
//    s_resp.write_to_file("hw3_out/P1_comb1_responses/energy_" + filter_names.at(i) + ".raw");
//  }
//  
//  Mat wrapped_kmeans = filter_energy.generate_kmeans(500, 425, 4);
//  Picture leveled = Picture("", 500, 425, COLOR_GRAY);
//  leveled.slurp(filter_energy.unwrap_kmeans(wrapped_kmeans, 500, 4));
//  leveled.write_to_file("hw3_out/P1_comb1_responses/leveled.raw");
  
  Picture comb2 = Picture("hw3_images/P1/Comb_2.raw", 512, 512, COLOR_GRAY);
  int window_radius = 13;
  
  comb2.extend_boundary(boundary_extension);
  comb2.copy_result_to_data(true);
  comb2.subtract_average_to_laws_workspace();
  
  string prepath = enable_advanced ? "hw3_out/P1_comb2_adv_responses/resp_" : "hw3_out/P1_comb2_responses/resp_";
  
  for (int i = 0; i < laws_filter.filter_banks.size(); i++) {
    if (enable_advanced) {
      if (!is_in_vector(comb2_selected, i)) {
        continue;
      }
    }
    Matrix filter = laws_filter.filter_banks.at(i);
    vector<float> unwrapped_filter = filter.unwrap();
    comb2.apply_laws_filter(unwrapped_filter, boundary_extension);
    
    float avg = comb2.average_laws_response(boundary_extension);
    
    comb2.normalize_laws_filter_response(boundary_extension);
    comb2.copy_result_to_data();
    comb2.crop(2, 2, 513, 513);
    
    
    
    comb2.write_to_file(prepath + filter_names.at(i) + ".raw");
    Picture s_resp = Picture(prepath + filter_names.at(i) + ".raw", 512, 512, COLOR_GRAY);
    s_resp.copy_data_to_result();
    vector<vector<float>> energy = s_resp.window_laws_response(window_radius);
    filter_energy.add(energy);
    //s_resp.slurp(energy);
    //s_resp.write_to_file("hw3_out/P1_comb1_responses/energy_" + filter_names.at(i) + ".raw");
  }
  
  wrapped_kmeans = filter_energy.generate_kmeans(512, 512, 6, true);
  leveled = Picture("", 512, 512, COLOR_GRAY);
  leveled.slurp(filter_energy.unwrap_kmeans(wrapped_kmeans, 512, 6));
  leveled.write_to_file(prepath + "leveled_" + to_string(window_radius) + ".raw");
}

void f_3_1_segmentation_with_bypass() {

}