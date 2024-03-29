//
//  run_3_1_postprocess_segment.cpp
//  ee569
//
//  Created by Gloria Budiman on 11/1/16.
//  Finalized on 11/3/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
#include "FilterEnergy.hpp"
using namespace std;
using namespace cv;

void f_3_1_postprocess_segment() {
  int gaussian_radius = 101;
  Mat p = Picture("hw3_images/P1/Comb_2.raw", 512, 512, COLOR_GRAY).to_cv2_mat();
  GaussianBlur(p, p, Size(gaussian_radius, gaussian_radius), 0);
  Picture q = Picture("", 512, 512, COLOR_GRAY);
  q.slurp_cv2_mat(p);
  q.write_to_file("hw3_out/P1_comb2_preprocess/comb2.raw");
  
  cout << "Running histogram peak extraction..." << endl;
  Picture p_comb2 = Picture("hw3_out/P1_comb2_preprocess/comb2.raw", 512, 512, COLOR_GRAY);
  p_comb2.get_peak_hist(3, 24);
  p_comb2.write_to_file("hw3_out/P1_comb2_preprocess/comb2_filt.raw");
  
  cout << "Running spatial-intensity-based segmentation..." << endl;
  Picture p_combsec2 = Picture("hw3_out/P1_comb2_preprocess/comb2_filt.raw", 512, 512, COLOR_GRAY);
  p_combsec2.segment_base(3);
  p_combsec2.write_to_file("hw3_out/P1_comb2_preprocess/comb2_dissplit.raw");
  
  cout << "Running contour-guided segmentation..." << endl;
  Picture p_combseparated2 = Picture("hw3_out/P1_comb2_preprocess/comb2_dissplit.raw", 512, 512, COLOR_GRAY);
  Picture p_pca_reduced2 = Picture("hw3_out/P1_comb2_adv_responses/resp_leveled_13.raw", 512, 512, COLOR_GRAY);
  p_combseparated2.guide_contour(p_pca_reduced2);
  p_combseparated2.write_to_file("hw3_out/P1_comb2_preprocess/comb2_guided.raw");
  
}
