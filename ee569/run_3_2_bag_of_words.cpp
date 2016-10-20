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

void extract_descriptor(Mat img, Mat& training_descriptors, Mat& individual_descriptor) {
  vector<KeyPoint> keypoints;
  
  auto sift_detector = xfeatures2d::SIFT::create();
  auto sift_extractor = xfeatures2d::SiftDescriptorExtractor::create();
  sift_detector->detect(img, keypoints);
  sift_extractor->compute(img, keypoints, individual_descriptor);
  
  training_descriptors.push_back(individual_descriptor);
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

void make_histogram_plot(Mat data) {
  int hist_size = 8;
  float range[] = { 0, 8 };
  const float* hist_range = { range };
  bool uniform = true; bool accumulate = false;
  Mat result;
  calcHist(&data, 1, 0, Mat(), result, 1, &hist_size, &hist_range, uniform, accumulate);
  
  cout << result << endl;
  int z = 0;
}

void extract_codewords(Mat data) {
  vector<KeyPoint> keypoints;
  Mat descriptors;
  
  auto sift_detector = xfeatures2d::SIFT::create();
  auto sift_extractor = xfeatures2d::SiftDescriptorExtractor::create();
  sift_detector->detect(data, keypoints);
  sift_extractor->compute(data, keypoints, descriptors);
  
  BOWKMeansTrainer bow_trainer(8);
  bow_trainer.add(descriptors);
  Mat vocabulary = bow_trainer.cluster();
  
  make_histogram_plot(vocabulary);
}

int compute_euclidean_distance(Mat codebook, Mat row) {
  vector<float> e_distances = vector<float>();
  
  int cols = row.cols;
  
  for (int i = 0; i < codebook.rows; i++) {
    float e_distance = 0;
    for (int j = 0; j < cols; j++) {
      float codebook_cell = codebook.at<float>(i, j);
      float row_cell = row.at<float>(0, j);
      
      e_distance += pow((codebook_cell - row_cell), 2);
    }
    
    e_distances.push_back(e_distance);
  }
  
  float min = numeric_limits<float>::max();
  int index = -1;
  for (int i = 0; i < e_distances.size(); i++) {
    float dist = e_distances.at(i);
    if (dist < min) {
      min = dist;
      index = i;
    }
  }
  
  return index;
}

vector<int> fit_codewords(Mat codebook, Mat descriptors) {
  vector<int> hists = vector<int>(8);
  
  for (int i = 0; i < descriptors.rows; i++) {
    int min_dist = compute_euclidean_distance(codebook, descriptors.row(i));
    hists.at(min_dist)++;
  }
  
  return hists;
}

void print_vector(vector<int> in) {
  for (int i = 0; i < in.size(); i++) {
    printf("%4d ", in.at(i));
  }
  
  printf("\n");
}

int histogram_difference(vector<int> a, vector<int> b) {
  int diff = 0;
  for (int i = 0; i < a.size(); i++) {
    int ax = a.at(i);
    int bx = b.at(i);
    diff += pow((ax - bx), 2);
  }
  
  return diff;
}

void f_3_2_bag_of_words() {
  Mat jeep = imread("hw3_images/P2/Jeep.jpg");
  Mat bus = imread("hw3_images/P2/Bus.jpg");
  Mat rav1 = imread("hw3_images/P2/rav4_1.jpg");
  Mat rav2 = imread("hw3_images/P2/rav4_2.jpg");
  
  Mat training_descriptors;
  Mat jeep_descriptor, bus_descriptor, rav1_descriptor, rav2_descriptor;
  
  extract_descriptor(jeep, training_descriptors, jeep_descriptor);
  extract_descriptor(bus, training_descriptors, bus_descriptor);
  extract_descriptor(rav1, training_descriptors, rav1_descriptor);
  //extract_descriptor(rav2, training_descriptors);
  
  BOWKMeansTrainer bow_trainer(8);
  bow_trainer.add(training_descriptors);
  Mat vocabulary = bow_trainer.cluster();
  
  // ignore rav2 descriptor, aka don't put it into codebook
  extract_descriptor(rav2, training_descriptors, rav2_descriptor);
  
  vector<int> jeep_hist = fit_codewords(vocabulary, jeep_descriptor);
  vector<int> bus_hist = fit_codewords(vocabulary, bus_descriptor);
  vector<int> rav1_hist = fit_codewords(vocabulary, rav1_descriptor);
  vector<int> rav2_hist = fit_codewords(vocabulary, rav2_descriptor);
  
  print_vector(jeep_hist);
  print_vector(bus_hist);
  print_vector(rav1_hist);
  print_vector(rav2_hist);
  
  cout << histogram_difference(jeep_hist, rav2_hist) << endl;
  cout << histogram_difference(bus_hist, rav2_hist) << endl;
  cout << histogram_difference(rav1_hist, rav2_hist) << endl;
  
//  make_histogram_plot(vocabulary);
//  Ptr<DescriptorExtractor> extractor = xfeatures2d::SiftDescriptorExtractor::create();
//  Ptr<DescriptorMatcher> matcher = new FlannBasedMatcher();
//  BOWImgDescriptorExtractor bow_de(extractor, matcher);
//  
//  bow_de.setVocabulary(vocabulary);
//  
//  map<string, Mat> classes_training_data;
//  
//  extract_codewords(jeep);
//  extract_codewords(bus);
//  extract_codewords(rav1);
//  extract_codewords(rav2);
//  
//  int z = 0;
  
//  vector<KeyPoint> kp_jeep, kp_bus, kp_rav1;
//  Mat d_jeep, d_bus, d_rav1;
//
//  Mat dict_jeep = make_bow_cluster(jeep, "jeep", kp_jeep, d_jeep);
//  Mat dict_bus = make_bow_cluster(bus, "bus", kp_bus, d_bus);
//  Mat dict_rav1 = make_bow_cluster(rav1, "rav1", kp_rav1, d_rav1);
//  
//  //bow_match(jeep, dict_jeep, kp_jeep, d_jeep, rav2);
//  bow_match(dict_jeep, jeep, kp_jeep, d_jeep, rav2, "jeep");
//  bow_match(dict_bus, bus, kp_bus, d_bus, rav2, "bus");
//  bow_match(dict_rav1, rav1, kp_rav1, d_rav1, rav2, "rav1");
}


