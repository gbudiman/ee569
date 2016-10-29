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

int g_threshold_parameter = 127;
int const g_max_threshold = 255;
Mat g_thresholded;
Mat g_thresholded_display;

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
    f_measure.result.write_to_file(base_path + "_annot.raw");
  }
}

void g_threshold_callback (int, void*) {
  g_thresholded_display = Scalar::all(0);

  threshold(g_thresholded, g_thresholded_display, g_threshold_parameter, 255, THRESH_BINARY_INV);
  printf("Threshold: %d\n", g_threshold_parameter);
  g_thresholded_display = Scalar::all(255) - g_thresholded_display;
  imshow("Threshold", g_thresholded_display);
}

void g_write_output(string out) {
  imwrite(out, g_thresholded_display);
}

void g_cycle(Mat img, string path_out) {
  //img.convertTo(img, DataType<float>::type, 1/255.0);
  
  g_thresholded = img;
  
  namedWindow("Threshold", CV_WINDOW_AUTOSIZE);
  imshow("Edges", g_thresholded);
  
  createTrackbar("Threshold", "Threshold", &g_threshold_parameter, g_max_threshold, g_threshold_callback);
  g_threshold_callback(0, 0);
  waitKey(0);
  g_write_output(path_out);
}

void f_3_3_ground_truth() {
  g_cycle(imread("hw3_out/P3_edge_map/elephant.png"), "hw3_out/P3_edge_map/elephant_thresholded.png");
  mass_process("hw3_out/P3_edge_map/elephant_thresholded.png", "hw3_images/P3/Elephant_gt", 481, 321, 6);
  
  g_cycle(imread("hw3_out/P3_edge_map/jaguar.png"), "hw3_out/P3_edge_map/jaguar_thresholded.png");
  mass_process("hw3_out/P3_edge_map/jaguar_thresholded.png", "hw3_images/P3/Jaguar_gt", 481, 321, 6);
  
  g_cycle(imread("hw3_out/P3_edge_map/zebra.png"), "hw3_out/P3_edge_map/zebra_thresholded.png");
  mass_process("hw3_out/P3_edge_map/zebra_thresholded.png", "hw3_images/P3/Zebra_gt", 481, 321, 5);
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
