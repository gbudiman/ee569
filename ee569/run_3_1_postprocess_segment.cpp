//
//  run_3_1_postprocess_segment.cpp
//  ee569
//
//  Created by Gloria Budiman on 11/1/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
using namespace std;
using namespace cv;

void f_3_1_postprocess_segment() {
  int gaussian_radius = 91;
  Mat p = Picture("hw3_images/P1/Comb_2.raw", 512, 512, COLOR_GRAY).to_cv2_mat();
  GaussianBlur(p, p, Size(gaussian_radius, gaussian_radius), 0);
  Picture q = Picture("", 512, 512, COLOR_GRAY);
  q.slurp_cv2_mat(p);
  q.write_to_file("hw3_out/P1_comb2_preprocess/comb2.raw");
  
  Picture p_comb2 = Picture("hw3_out/P1_comb2_preprocess/comb2.raw", 512, 512, COLOR_GRAY);
  p_comb2.get_peak_hist(6, 5);
  p_comb2.write_to_file("hw3_out/P1_comb2_preprocess/comb2_filt.raw");
}
