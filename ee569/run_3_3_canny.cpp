//
//  run_3_3_canny.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/16/16.
//  Finalized on 10/31/16
//  gbudiman@usc.edu 6528-1836-50
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

int canny_ratio = 30;
int const max_canny_ratio = 1000;
int canny_divisor = 10;

int kernel_size = 0;
int const max_kernel_size = 2;

void draw() {
  
  dst = Scalar::all(0);
  src.copyTo(dst, detected_edges);
  imshow(window_name, dst);
}

void canny_threshold(int, void*) {
  int real_kernel_size = (kernel_size + 1) * 2 + 1;
  blur(src_gray, detected_edges, Size(real_kernel_size, real_kernel_size));
  
  printf("[%d]: %d x %.2f => %.2f\n",
         real_kernel_size,
         low_threshold,
         (float) canny_ratio / canny_divisor,
         low_threshold * ((float) canny_ratio / canny_divisor));
  
  Canny(detected_edges, detected_edges, low_threshold, low_threshold * ((float) canny_ratio / canny_divisor), real_kernel_size);
  draw();
}

void process(string outpath) {
  dst.create(src.size(), src.type());
  cvtColor(src, src_gray, CV_RGB2GRAY);
  
  namedWindow(window_name, CV_WINDOW_AUTOSIZE);
  createTrackbar("Min Threshold", window_name, &low_threshold, max_low_threshold, canny_threshold);
  createTrackbar("Ratio / 100", window_name, &canny_ratio, max_canny_ratio, canny_threshold);
  createTrackbar("Kernel [3/5/7]", window_name, &kernel_size, max_kernel_size, canny_threshold);
  canny_threshold(0, 0);
  waitKey(0);
  imwrite(outpath, dst);
}

void f_3_3_canny() {
  src = Picture("hw3_images/P3/Zebra.raw", 481, 321, COLOR_RGB).to_cv2_mat();
  process("hw3_out/P3_canny/Zebra.png");

  src = Picture("hw3_images/P3/Jaguar.raw", 481, 321, COLOR_RGB).to_cv2_mat();
  process("hw3_out/P3_canny/Jaguar.png");
}
