//
//  run_2_3_a_rice_grain.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/22/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Coordinate.hpp"
#include "Picture.hpp"
#include "GrainCategorizer.hpp"
#include "SpatialData.hpp"
#include "KCluster.hpp"
using namespace std;

void f_2_3_a_rice_grain() {
  Picture rg = Picture("hw2_images/Rice.raw", 690, 500, COLOR_RGB);
  rg.to_grayscale();
  rg.write_to_file("hw2_out/Rice_gray.raw");
  
  Picture rgray = Picture("hw2_out/Rice_gray.raw", 690, 500, COLOR_GRAY);
  rgray.prepare_gnuplot_histogram_data("hw2_out/Rice_gray.raw", STRIP_EXTENSION);
  rgray.adaptive_thresholding2(75);
  rgray.write_to_file("hw2_out/Rice_thresholded.raw");

  Picture rth = Picture("hw2_out/Rice_thresholded.raw", 690, 500, COLOR_GRAY);
  rth.morph(MORPH_THIN);
  rth.write_to_file("hw2_out/Rice_thinning.raw");
  
  rth = Picture("hw2_out/Rice_thresholded.raw", 690, 500, COLOR_GRAY);
  rth.morph(MORPH_ERODE);
  //vector<Coordinate> centers = rth.get_center_of_mass();
  rth.write_to_file("hw2_out/Rice_eroding.raw");

  rth = Picture("hw2_out/Rice_eroding.raw", 690, 500, COLOR_GRAY);
  vector<Coordinate> centers = rth.get_center_of_mass();

  GrainCategorizer gc = GrainCategorizer();
  
  
  rth = Picture("hw2_out/Rice_thresholded.raw", 690, 500, COLOR_GRAY);
  vector<SpatialData> s = rth.measure_area(centers);
  vector<SpatialData> chromas = rth.measure_chromaticity(rg, centers);
  //rth.write_to_file("hw2_out/Rice_area.raw");
  
  for (int i = 0; i < s.size(); i++) {
    gc.insert_area_data(s.at(i).spatial_center, s.at(i).area);
  }
  
  for (int i = 0; i < chromas.size(); i++) {
    gc.correlate_chroma(chromas.at(i).spatial_center, chromas.at(i).chroma);
  }
  
  rth = Picture("hw2_out/Rice_thinning.raw", 690, 500, COLOR_GRAY);
  vector<SpatialData> l = rth.measure_length();
  
  for (int i = 0; i < l.size(); i++) {
    gc.correlate_length(l.at(i).bounding_box, l.at(i).length);
  }
  
//  printf("==== by area\n");
//  gc.cluster_group_by_area();
//  gc.debug_groups();
//  
//  printf("==== by roundness\n");
//  gc.cluster_group_by_roundness();
//  gc.debug_groups();
//  
//  printf("==== by lightness\n");
//  gc.cluster_group_by_lightness();
//  gc.debug_groups();
  
  printf("====\n");
  printf("  Center   | Area |  Len x Wid  | Round |    RGB Mean   | Lum  | Yel  |  Red   // Group\n");
  gc.cluster_group_by_location();
  gc.debug_groups();
  
//  printf("==== by yellow chromaticity\n");
//  gc.cluster_group_by_yellow_chroma();
//  gc.debug_groups();
//  
//  printf("==== by red chromaticity\n");
//  gc.cluster_group_by_red_chroma();
//  gc.debug_groups();
  
  gc.compute_average_size();
  KCluster kcc = gc.categorize_by_kmeans();
  for (int i = 0; i < kcc.data.size(); i++) {
    rth = Picture("hw2_out/Rice_thresholded.raw", 690, 500, COLOR_GRAY);
    vector<Coordinate> group_centers = vector<Coordinate>();
    for (int j = 0; j < kcc.data.at(i).size(); j++) {
      group_centers.push_back(kcc.data.at(i).at(j).first);
    }
    rth.measure_area(group_centers);
    
    Picture gp = Picture("hw2_out/Rice_gray.raw", 690, 500, COLOR_GRAY);
    gp.highlight_overlay(rth.get_result_gray());
    
    string out_path = "hw2_out/Rice_overlay_" + to_string(i) + ".raw";
    
    gp.write_to_file(out_path);
    int z = 0;
  }
  
  //rth.write_to_file("hw2_out/Rice_traced.raw");
  
//  rth = Picture("hw2_out/Rice_thresholded.raw", 690, 500, COLOR_GRAY);
//  rth.morph(MORPH_SKEL);
//  rth.write_to_file("hw2_out/Rice_skeleton.raw");
  
//  rth.crop(168, 394, 302, 480); // 135x87
//  rth.write_to_file("hw2_out/Rice_thresholded_cropped.raw");
  
//  Picture rth_small = Picture("hw2_out/Rice_thresholded_cropped.raw", 135, 87, COLOR_GRAY);
//  rth_small.morph_thin();
//  rth_small.write_to_file("hw2_out/Rsmall_thinning.raw");
  
/////////////////////////////////////
// below this line is incorrect
//
//  Picture rth = Picture("hw2_out/Rice_thresholded.raw", 690, 500, COLOR_GRAY);
//  rth.morph_erode();
//  rth.write_to_file("hw2_out/Rice_erode.raw");
//  
//  Picture reroded = Picture("hw2_out/Rice_erode.raw", 690, 500, COLOR_GRAY);
//  reroded.post_process_threshold();
//  reroded.write_to_file("hw2_out/Rice_thrpp.raw");
  
//  Picture rpp = Picture("hw2_out/Rice_thrpp.raw", 690, 500, COLOR_GRAY);
//  rpp.morph_erode();
//  rpp.copy_result_to_data();
//  GrainCategorizer gc = rpp.count_objects();
//  rpp.write_to_file("hw2_out/Rice_counted.raw");
//  
//  rpp = Picture("hw2_out/Rice_thrpp.raw", 690, 500, COLOR_GRAY);
//  rpp.compute_spatial_data(gc);
//  rpp.write_to_file("hw2_out/Rice_expanded.raw");
}

void f_rice(char* in, int x, int y, int mode) {
  Picture rg = Picture(in, x, y, mode);
  rg.to_grayscale();
  rg.write_to_file("hw2_out/Rice_gray.raw");
  
  Picture rgray = Picture("hw2_out/Rice_gray.raw", x, y, COLOR_GRAY);

  printf("Running adaptive thresholding with window size 75...\n");
  rgray.adaptive_thresholding2(75);
  rgray.write_to_file("hw2_out/Rice_thresholded.raw");
  
  Picture rth = Picture("hw2_out/Rice_thresholded.raw", x, y, COLOR_GRAY);
  rth.morph(MORPH_THIN);
  rth.write_to_file("hw2_out/Rice_thinning.raw");
  
  rth = Picture("hw2_out/Rice_thresholded.raw", x, y, COLOR_GRAY);
  rth.morph(MORPH_ERODE);
  rth.write_to_file("hw2_out/Rice_eroding.raw");
  
  Picture reroded = Picture("hw2_out/Rice_eroding.raw", x, y, COLOR_GRAY);
  rth = Picture("hw2_out/Rice_thresholded.raw", x, y, COLOR_GRAY);
  vector<Coordinate> centers = reroded.get_center_of_mass();
  vector<SpatialData> s = rth.measure_area(centers);
  vector<SpatialData> chromas = rth.measure_chromaticity(rg, centers);
  
  GrainCategorizer gc = GrainCategorizer();
  
  for (int i = 0; i < s.size(); i++) {
    gc.insert_area_data(s.at(i).spatial_center, s.at(i).area);
  }
  
  for (int i = 0; i < chromas.size(); i++) {
    gc.correlate_chroma(chromas.at(i).spatial_center, chromas.at(i).chroma);
  }
  
  rth = Picture("hw2_out/Rice_thinning.raw", x, y, COLOR_GRAY);
  vector<SpatialData> l = rth.measure_length();
  
  for (int i = 0; i < l.size(); i++) {
    gc.correlate_length(l.at(i).bounding_box, l.at(i).length);
  }
  
  printf("  Center   | Area |  Len x Wid  | Round |    RGB Mean   | Lum  | Yel  |  Red   // Group\n");
  gc.cluster_group_by_location();
  gc.debug_groups();
  
  gc.compute_average_size();
  
  
  KCluster kcc = gc.categorize_by_kmeans();
  for (int i = 0; i < kcc.data.size(); i++) {
    rth = Picture("hw2_out/Rice_thresholded.raw", 690, 500, COLOR_GRAY);
    vector<Coordinate> group_centers = vector<Coordinate>();
    for (int j = 0; j < kcc.data.at(i).size(); j++) {
      group_centers.push_back(kcc.data.at(i).at(j).first);
    }
    rth.measure_area(group_centers);
    
    Picture gp = Picture("hw2_out/Rice_gray.raw", 690, 500, COLOR_GRAY);
    gp.highlight_overlay(rth.get_result_gray());
    
    string out_path = "hw2_out/Rice_overlay_" + to_string(i) + ".raw";
    
    gp.write_to_file(out_path);
    int z = 0;
  }
}
