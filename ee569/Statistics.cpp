//
//  Statistics.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/11/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Statistics.hpp"
using namespace std;

Statistics::Statistics() {
  data = vector<vector<float>>();
}

void Statistics::add_row(vector<float> in) {
  data.push_back(in);
}

vector<float> Statistics::compute_column_mean() {
  mean = vector<float>();
  vector<float> sums = vector<float>(data.at(0).size());
  
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data.at(i).size(); j++) {
      sums.at(j) += data.at(i).at(j);
    }
  }
  
  for (int i = 0; i < sums.size(); i++) {
    //sums.at(i) /= data.size();
    mean.push_back(sums.at(i) / data.size());
  }
  
  return mean;
}

vector<float> Statistics::compute_column_variance() {
  if (mean.size() == 0) { compute_column_mean(); }
  
  variance = vector<float>();
  vector<float> diff_squared_sums = vector<float>(data.at(0).size());
  
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data.at(i).size(); j++) {
      diff_squared_sums.at(j) += pow(data.at(i).at(j) - mean.at(j), 2);
    }
  }
  
  for (int i = 0; i < diff_squared_sums.size(); i++) {
    variance.push_back(sqrt(diff_squared_sums.at(i) / data.size()));
  }
  
  return variance;
}