//
//  run_3_1_texture.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/10/16.
//  Finalized on 10/31/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
#include "LawsFilter.hpp"
#include "Statistics.hpp"

using namespace std;
using namespace cv;

void process(Picture p) {
  
}

void f_3_1_texture() {
  int boundary_extension = 2;
  Statistics stats = Statistics();
  Mat m = Mat::zeros(12, 25, CV_32F);
  
  vector<string> filter_base = { "L5", "E5", "S5", "W5", "R5" };
  vector<string> filter_names = expand_filter_names(filter_base);
  vector<Picture> pictures = vector<Picture>();
  LawsFilter laws_filter = LawsFilter();
  
  for (int i = 1; i <= 12; i++) {
    pictures.push_back(Picture("hw3_images/P1/Texture" + to_string(i) + ".raw", 128, 128, COLOR_GRAY));
  }
  
  printf("Tex# ");
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
      base.normalize_laws_filter_response(boundary_extension);
      //base.write_to_file("hw3_out/P1_Laws_Texture_Response/Texture" + to_string(h + 1) + "_" + filter_names.at(i) + ".raw");
      float avg = base.average_laws_response(boundary_extension);
      
      avgs.push_back(avg);
      m.at<float>(h, i) = avg;
      base = pictures.at(h);
    }
    
    printf("%4d ", h + 1);
    for (int i = 0; i < filter_names.size(); i++) {
      printf("%7.1f ", avgs.at(i));
    }
    printf("\n");
    
    stats.add_row(avgs);
  }
  
  
  stats.compute_column_variance();
  printf("---- ");
  for (int i = 0; i < stats.variance.size(); i++) {
    printf("  ----  ");
  }
  
  printf("\n");
  
  printf(" Var ");
  for (int i = 0; i < stats.variance.size(); i++) {
    printf("%7.1f ", stats.variance.at(i));
  }
  
  printf("\n");
  
  Mat projection_result;
  Mat m_sliced = m(Rect(1, 0, 24, 12));
  //Mat m_sliced = m(Rect(0, 0, 25, 12));
  PCA pca = PCA(m_sliced, Mat(), PCA::DATA_AS_ROW, 3);
  pca.project(m_sliced, projection_result);
  cout << projection_result << endl;
  
  Mat best_labels;
  Mat centers;
  kmeans(projection_result, 4, best_labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 4000, 0.0001), 800, KMEANS_RANDOM_CENTERS, centers);
  cout << best_labels << endl;
  cout << centers << endl;
  
  Mat best_labels_unreduced;
  Mat centers_unreduced;
  kmeans(m, 4, best_labels_unreduced, TermCriteria(TermCriteria::EPS, 4000, 0.0001), 800, KMEANS_RANDOM_CENTERS, centers_unreduced);
  cout << best_labels_unreduced << endl;
  cout << centers_unreduced << endl;
}

