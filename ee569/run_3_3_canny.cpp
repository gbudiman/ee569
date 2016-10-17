//
//  run_3_3_canny.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/16/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"

using namespace cv;

Mat src, src_gray, dst;
Mat detected_edges;
char* window_name = "Canny Edge Detector";
int low_threshold;
int const max_low_threshold = 100;

int canny_ratio = 300;
int const max_canny_ratio = 1000;

void draw() {
  printf("%d x %.2f => %.2f\n", low_threshold, (float) canny_ratio / 100.0, low_threshold * ((float) canny_ratio / 100.0));
  dst = Scalar::all(0);
  src.copyTo(dst, detected_edges);
  imshow(window_name, dst);
}

void canny_threshold(int, void*) {
  blur(src_gray, detected_edges, Size(3, 3));
  Canny(detected_edges, detected_edges, low_threshold, low_threshold * ((float) canny_ratio / 100.0), 3);
  draw();
}

void func_canny_ratio(int, void*) {
  blur(src_gray, detected_edges, Size(3, 3));
  Canny(detected_edges, detected_edges, low_threshold, low_threshold * ((float) canny_ratio / 100.0), 3);
  draw();
}

void f_3_3_canny() {
  //CannyWrapper canny = CannyWrapper(Picture("hw3_images/P3/Zebra.raw", 481, 321, COLOR_RGB).to_cv2_mat());
  //canny.process();
  
  src = Picture("hw3_images/P3/Zebra.raw", 481, 321, COLOR_RGB).to_cv2_mat();
  dst.create(src.size(), src.type());
  cvtColor(src, src_gray, CV_RGB2GRAY);
  
  namedWindow(window_name, CV_WINDOW_AUTOSIZE);
  createTrackbar("Min Threshold", window_name, &low_threshold, max_low_threshold, canny_threshold);
  createTrackbar("Ratio / 100", window_name, &canny_ratio, max_canny_ratio, func_canny_ratio);
  canny_threshold(0, 0);
  waitKey(0);
  
}
