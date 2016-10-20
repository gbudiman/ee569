//
//  run_3_3_ground_truth.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/17/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "FMeasure.hpp"
using namespace cv;
using namespace std;

void mass_process(string base_path, string grounds_path, int x, int y, int ground_count) {
  printf("------------ %s ------------\n", base_path.c_str());
  Picture base = Picture::color_format_to_grayscale_raw(x, y, base_path);
  vector<Picture> ground_truths = vector<Picture>();
  for(int i = 1; i <= ground_count; i++) {
    Picture p = Picture(grounds_path + to_string(i) + ".raw", x, y, COLOR_GRAY);
    ground_truths.push_back(p);
  }
  
  FMeasure f_measure = FMeasure(base);
  for (int i = 0; i < ground_truths.size(); i++) {
    f_measure.compare_against(ground_truths.at(i));
  }
}

void f_3_3_ground_truth() {
  mass_process("hw3_out/P3/Elephant_emt.png", "hw3_images/P3/Elephant_gt", 481, 321, 6);
  mass_process("hw3_out/P3/Jaguar_emt.png", "hw3_images/P3/Jaguar_gt", 481, 321, 6);
  mass_process("hw3_out/P3/Zebra_emt.png", "hw3_images/P3/Zebra_gt", 481, 321, 5);
}

void f_3_3_ground_truth_e() {
//  Picture base = Picture("", 481, 321, COLOR_GRAY);
//  Mat base_mat = imread("hw3_out/P3/Elephant_emt.png");
//  cvtColor(base_mat, base_mat, COLOR_RGB2GRAY);
//  base.slurp(base_mat);
//  base.copy_result_to_data();
  
  Picture base = Picture::color_format_to_grayscale_raw(481, 321, "hw3_out/P3/Elephant_emt.png");
//  base.invert();
//  base.morph(MORPH_THINNING);
//  
//  base.copy_result_to_data();
//  base.invert();
//  base.write_to_file("hw3_out/P3/Elephant_thinning.raw");
  
  vector<Picture> elephants = vector<Picture>();
  
  for(int i = 1; i <=6; i++) {
//    Picture p = Picture::color_format_to_grayscale_raw(481, 321, "hw3_images/P3/Elephant_gt" + to_string(i) + ".raw");
    Picture p = Picture("hw3_images/P3/Elephant_gt" + to_string(i) + ".raw", 481, 321, COLOR_GRAY);
    elephants.push_back(p);
  }
  
  FMeasure f_measure = FMeasure(base);
  for (int i = 0; i < elephants.size(); i++) {
    f_measure.compare_against(elephants.at(i));
    //f_measure.result.write_to_file("hw3_out/P3/Elephant_annot.raw");
  }
}
