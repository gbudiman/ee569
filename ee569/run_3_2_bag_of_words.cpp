//
//  run_3_2_bag_of_words.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/14/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
using namespace cv;
using namespace std;

Mat make_bow_cluster(Mat imgmat, string dict, vector<KeyPoint>& kp_img, Mat& d_img) {
  BOWKMeansTrainer bow_jeep = BOWKMeansTrainer(8);
  
  auto sift_img = xfeatures2d::SIFT::create();
  
  sift_img->detect(imgmat, kp_img);
  sift_img->compute(imgmat, kp_img, d_img);
  bow_jeep.add(d_img);
  
  Mat vocab_jeep = bow_jeep.cluster();
  
  FileStorage fs("hw3_out/P2_BOW/" + dict + ".yml", FileStorage::WRITE);
  fs << "vocabulary" << vocab_jeep;
  fs.release();
  
  return vocab_jeep;
}

void bow_match(Mat dictionary, Mat base, vector<KeyPoint> base_keypoint, Mat base_descriptor, Mat input, string s_name) {
//void bow_match(Mat base, Mat dictionary, vector<KeyPoint> base_keypoint, Mat base_descriptor, Mat input) {
  Mat img_matches;
  
  Ptr<DescriptorMatcher> matcher(new FlannBasedMatcher);
  Ptr<FeatureDetector> detector(xfeatures2d::SiftFeatureDetector::create());
  Ptr<DescriptorExtractor> extractor(xfeatures2d::SiftDescriptorExtractor::create());
  
  BOWImgDescriptorExtractor bow_de(extractor, matcher);
  
  vector<KeyPoint> input_keypoint;
  detector->detect(input, input_keypoint);
  Mat input_descriptor;
  
  bow_de.setVocabulary(dictionary);
  bow_de.compute(input, input_keypoint, input_descriptor);
  
  vector<DMatch> matches;
  matcher->match(input_descriptor, base_descriptor, matches);
  drawMatches(input, input_keypoint, base, base_keypoint, matches, img_matches);
  
  imwrite("hw3_out/P2_BOW/m_" + s_name + ".jpg", img_matches);
}

void f_3_2_bag_of_words() {
  Mat jeep = imread("hw3_images/P2/Jeep.jpg");
  Mat bus = imread("hw3_images/P2/Bus.jpg");
  Mat rav1 = imread("hw3_images/P2/rav4_1.jpg");
  Mat rav2 = imread("hw3_images/P2/rav4_2.jpg");
  
  vector<KeyPoint> kp_jeep, kp_bus, kp_rav1;
  Mat d_jeep, d_bus, d_rav1;

  Mat dict_jeep = make_bow_cluster(jeep, "jeep", kp_jeep, d_jeep);
  Mat dict_bus = make_bow_cluster(bus, "bus", kp_bus, d_bus);
  Mat dict_rav1 = make_bow_cluster(rav1, "rav1", kp_rav1, d_rav1);
  
  //bow_match(jeep, dict_jeep, kp_jeep, d_jeep, rav2);
  bow_match(dict_jeep, jeep, kp_jeep, d_jeep, rav2, "jeep");
  bow_match(dict_bus, bus, kp_bus, d_bus, rav2, "bus");
  bow_match(dict_rav1, rav1, kp_rav1, d_rav1, rav2, "rav1");
  int z = 0;
}
