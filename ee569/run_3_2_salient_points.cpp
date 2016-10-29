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

vector<DMatch> min_max_distance(Mat descriptors, vector<DMatch> matches, double min_threshold = 0.02, double hard_threshold = 0.3) {
  vector<DMatch> good_matches;
  double max_dist = numeric_limits<double>::min();
  double min_dist = numeric_limits<double>::max();
  
  for (int i = 0; i < descriptors.rows; i++) {
    double dist = matches[i].distance;
    if (dist < min_dist) { min_dist = dist; }
    if (dist > max_dist) { max_dist = dist; }
  }
  
  printf("Dist: (%.2f) -> (%.2f)\n", min_dist, max_dist);
  
  for (int i = 0; i < descriptors.rows; i++) {
    if (matches[i].distance <= min(max(2 * min_dist, min_threshold), hard_threshold)) {
      good_matches.push_back(matches[i]);
    }
  }
  
  printf("%d reduced to %d good matches\n", matches.size(), good_matches.size());
  return good_matches;
}

void f_3_2_salient_points() {
  //Mat jeep = imread("hw3_images/P2/Jeep.jpg");
  Mat jeep = Picture("hw3_images/P2/Jeep.raw", 500, 380, COLOR_RGB).to_cv2_mat();
  
  //Mat bus = imread("hw3_images/P2/Bus.jpg");
  Mat bus = Picture("hw3_images/P2/Bus.raw", 450, 240, COLOR_RGB).to_cv2_mat();

  Mat output;
  //Mat jeep_m = Mat::zeros(500, 380, CV_8UC3);
  
  cvtColor(jeep, jeep, COLOR_RGB2GRAY);
  cvtColor(bus, bus, COLOR_RGB2GRAY);
  Ptr<Feature2D> f2d = xfeatures2d::SIFT::create(0, 3, 0.1, 5, 1.6);
  vector<KeyPoint> keypoints_bus, keypoints_jeep;
  
  f2d->detect(jeep, keypoints_jeep);
  cout << "keypoints found: " << keypoints_jeep.size() << endl;
  drawKeypoints(jeep, keypoints_jeep, output, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  imwrite("hw3_out/P2/Jeep_SIFT.png", output);
  
  f2d->detect(bus, keypoints_bus);
  cout << "keypoints found: " << keypoints_bus.size() << endl;
  drawKeypoints(bus, keypoints_bus, output, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  imwrite("hw3_out/P2/Bus_SIFT.png", output);
  
  
  Ptr<Feature2D> s2d = xfeatures2d::SURF::create(15000);
  s2d->detect(jeep, keypoints_jeep);
  cout << "keypoints found: " << keypoints_jeep.size() << endl;
  drawKeypoints(jeep, keypoints_jeep, output, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  imwrite("hw3_out/P2/Jeep_SURF.png", output);
  
  s2d = xfeatures2d::SURF::create(15000);
  s2d->detect(bus, keypoints_bus);
  cout << "keypoints found: " << keypoints_bus.size() << endl;
  drawKeypoints(bus, keypoints_bus, output, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  imwrite("hw3_out/P2/Bus_SURF.png", output);
  
  ////////////////////////////////////////////////
  Mat rav1 = Picture("hw3_images/P2/rav4_1.raw", 500, 256, COLOR_RGB).to_cv2_mat();
  Mat rav2 = Picture("hw3_images/P2/rav4_2.raw", 500, 256, COLOR_RGB).to_cv2_mat();
  
  vector<KeyPoint> kp1, kp2;
  Mat descriptors1, descriptors2, img_matches, descriptors_jeep, descriptors_bus;
  
  auto detector = xfeatures2d::SURF::create(5000);
  detector->detect(rav1, kp1);
  detector->detect(rav2, kp2);
  detector->detect(jeep, keypoints_jeep);
  detector->detect(bus, keypoints_bus);
  
  detector->compute(rav1, kp1, descriptors1);
  detector->compute(rav2, kp2, descriptors2);
  detector->compute(jeep, keypoints_jeep, descriptors_jeep);
  detector->compute(bus, keypoints_bus, descriptors_bus);
  
  auto matcher = FlannBasedMatcher();
  vector<DMatch> matches;
  vector<DMatch> good_matches;
  matcher.match(descriptors1, descriptors2, matches);
  
  good_matches = min_max_distance(descriptors1, matches, 0.25);
  drawMatches(rav1, kp1, rav2, kp2, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::DEFAULT);
  imwrite("hw3_out/P2/SURF_Rav_matches.png", img_matches);
  
  matcher.match(descriptors1, descriptors_jeep, matches);
  good_matches = min_max_distance(descriptors1, matches, 0.05);
  drawMatches(rav1, kp1, jeep, keypoints_jeep, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::DEFAULT);
  imwrite("hw3_out/P2/SURF_Rav_jeep_matches.png", img_matches);
  
  matcher.match(descriptors1, descriptors_bus, matches);
  good_matches = min_max_distance(descriptors1, matches, 0.05);
  drawMatches(rav1, kp1, bus, keypoints_bus, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::DEFAULT);
  imwrite("hw3_out/P2/SURF_Rav_bus_matches.png", img_matches);
  
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
  good_matches = min_max_distance(descriptors1, matches, 250, 250);
  drawMatches(rav1, kp1, rav2, kp2, good_matches, img_matches);
  imwrite("hw3_out/P2/SIFT_Rav_matches.png", img_matches);
  
  matcher.match(descriptors1, descriptors_jeep, matches);
  good_matches = min_max_distance(descriptors1, matches, 250, 250);
  drawMatches(rav1, kp1, jeep, keypoints_jeep, good_matches, img_matches);
  imwrite("hw3_out/P2/SIFT_Rav_jeep_matches.png", img_matches);
  
  matcher.match(descriptors1, descriptors_bus, matches);
  good_matches = min_max_distance(descriptors1, matches, 250, 250);
  drawMatches(rav1, kp1, bus, keypoints_bus, good_matches, img_matches);
  imwrite("hw3_out/P2/SIFT_Rav_bus_matches.png", img_matches);
}
