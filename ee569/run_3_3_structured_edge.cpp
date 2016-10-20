//
//  run_3_3_structured_edge.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/17/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
using namespace cv;
using namespace cv::ximgproc;

int threshold_parameter = 127;
int const max_threshold = 255;
Mat thresholded;
Mat thresholded_display;

void threshold_callback (int, void*) {
  thresholded_display = Scalar::all(0);
  threshold(thresholded, thresholded_display, threshold_parameter, 255, THRESH_BINARY_INV);
  imshow("Threshold", thresholded_display);
}

void write_output(string out) {
  imwrite(out, thresholded_display);
}

void cycle(Mat img, string path_out) {
  img.convertTo(img, DataType<float>::type, 1/255.0);
  
  Mat edges(img.size(), img.type());
  Ptr<StructuredEdgeDetection> sed = createStructuredEdgeDetection("ee569/model.yml.gz");
  
  namedWindow("Threshold", CV_WINDOW_AUTOSIZE);
  sed->detectEdges(img, edges);
  edges.convertTo(thresholded, DataType<uint8_t>::type, 255);
  imshow("Edges", edges);
  
  createTrackbar("Threshold", "Threshold", &threshold_parameter, max_threshold, threshold_callback);
  threshold_callback(0, 0);
  waitKey(0);
  write_output(path_out);
}

void f_3_3_structured_edge() {
  cycle(Picture("hw3_images/P3/Elephant.raw", 481, 321, COLOR_RGB).to_cv2_mat(), "hw3_out/P3/Elephant_emt.png");
  cycle(Picture("hw3_images/P3/Zebra.raw", 481, 321, COLOR_RGB).to_cv2_mat(), "hw3_out/P3/Zebra_emt.png");
  cycle(Picture("hw3_images/P3/Jaguar.raw", 481, 321, COLOR_RGB).to_cv2_mat(), "hw3_out/P3/Jaguar_emt.png");
}
