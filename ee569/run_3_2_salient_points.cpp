//
//  run_3_2_salient_points.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/12/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
using namespace cv;
using namespace std;

void f_3_2_salient_points() {
  Mat jeep = imread("hw3_images/P2/Jeep.jpg");
  Mat bus = imread("hw3_images/P2/Bus.jpg");

  Mat output;
  //Mat jeep_m = Mat::zeros(500, 380, CV_8UC3);
  
  Ptr<Feature2D> f2d = xfeatures2d::SIFT::create(0, 3, 0.1, 5, 2.7);
  vector<KeyPoint> keypoints_bus, keypoints_jeep;
  
  f2d->detect(jeep, keypoints_jeep);
  drawKeypoints(jeep, keypoints_jeep, output, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  imwrite("hw3_out/P2/Jeep_SIFT.jpg", output);
  
  f2d->detect(bus, keypoints_bus);
  drawKeypoints(bus, keypoints_bus, output, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  imwrite("hw3_out/P2/Bus_SIFT.jpg", output);
  
  
  Ptr<Feature2D> s2d = xfeatures2d::SURF::create(12500);
  s2d->detect(jeep, keypoints_jeep);
  drawKeypoints(jeep, keypoints_jeep, output, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  imwrite("hw3_out/P2/Jeep_SURF.jpg", output);
  
  s2d = xfeatures2d::SURF::create(16000);
  s2d->detect(bus, keypoints_bus);
  drawKeypoints(bus, keypoints_bus, output, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  imwrite("hw3_out/P2/Bus_SURF.jpg", output);
  
  ////////////////////////////////////////////////
  Mat rav1 = imread("hw3_images/P2/rav4_1.jpg");
  Mat rav2 = imread("hw3_images/P2/rav4_2.jpg");
  
  vector<KeyPoint> kp1, kp2;
  Mat descriptors1, descriptors2, img_matches, descriptors_jeep, descriptors_bus;
  
  auto detector = xfeatures2d::SURF::create(16000);
  detector->detect(rav1, kp1);
  detector->detect(rav2, kp2);
  detector->detect(jeep, keypoints_jeep);
  detector->detect(bus, keypoints_bus);
  
  detector->compute(rav1, kp1, descriptors1);
  cout << descriptors1 << endl;
  detector->compute(rav2, kp2, descriptors2);
  detector->compute(jeep, keypoints_jeep, descriptors_jeep);
  detector->compute(bus, keypoints_bus, descriptors_bus);
  
  auto matcher = BFMatcher();
  vector<DMatch> matches;
  matcher.match(descriptors1, descriptors2, matches);
  drawMatches(rav1, kp1, rav2, kp2, matches, img_matches);
  imwrite("hw3_out/P2/SURF_Rav_matches.jpg", img_matches);
  
  matcher.match(descriptors1, descriptors_jeep, matches);
  drawMatches(rav1, kp1, jeep, keypoints_jeep, matches, img_matches);
  imwrite("hw3_out/P2/SURF_Rav_jeep_matches.jpg", img_matches);
  
  matcher.match(descriptors1, descriptors_bus, matches);
  drawMatches(rav1, kp1, bus, keypoints_bus, matches, img_matches);
  imwrite("hw3_out/P2/SURF_Rav_bus_matches.jpg", img_matches);
  
  ////////////////////////////////////////////////
  f2d->detect(rav1, kp1);
  f2d->detect(rav2, kp2);
  f2d->detect(jeep, keypoints_jeep);
  f2d->detect(bus, keypoints_bus);
  
  f2d->compute(rav1, kp1, descriptors1);
  f2d->compute(rav2, kp2, descriptors2);
  f2d->compute(jeep, keypoints_jeep, descriptors_jeep);
  f2d->compute(bus, keypoints_bus, descriptors_bus);
  
  matcher.match(descriptors1, descriptors2, matches);
  drawMatches(rav1, kp1, rav2, kp2, matches, img_matches);
  imwrite("hw3_out/P2/SIFT_Rav_matches.jpg", img_matches);
  
  matcher.match(descriptors1, descriptors_jeep, matches);
  drawMatches(rav1, kp1, jeep, keypoints_jeep, matches, img_matches);
  imwrite("hw3_out/P2/SIFT_Rav_jeep_matches.jpg", img_matches);
  
  matcher.match(descriptors1, descriptors_bus, matches);
  drawMatches(rav1, kp1, bus, keypoints_bus, matches, img_matches);
  imwrite("hw3_out/P2/SIFT_Rav_bus_matches.jpg", img_matches);
}
