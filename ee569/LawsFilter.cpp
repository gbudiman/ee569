//
//  LawsFilter.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/10/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "LawsFilter.hpp"
using namespace std;

LawsFilter::LawsFilter() {
  filter_banks = vector<Matrix>();
  generate_filter_banks();
}

void LawsFilter::generate_filter_banks() {
  vector<vector<float>> base_matrices = vector<vector<float>>();
  
  vector<float> l5 = {1,4,6,4,1};
  vector<float> e5 = {-1,-2,0,2,1};
  vector<float> s5 = {-1,0,2,0,-1};
  vector<float> w5 = {-1,2,0,-2,1};
  vector<float> r5 = {1,-4,6,-4,1};
  
  base_matrices.push_back(l5);
  base_matrices.push_back(e5);
  base_matrices.push_back(s5);
  base_matrices.push_back(w5);
  base_matrices.push_back(r5);
  
  for (int i = 0; i < base_matrices.size(); i++) {
    Matrix multiplicator = Matrix(base_matrices.at(i), 5);
    for (int j = 0; j < base_matrices.size(); j++) {
      Matrix multiplicand = Matrix(base_matrices.at(j), 5).transpose();
      Matrix result = multiplicand.multiply(multiplicator);
      filter_banks.push_back(result);
    }
  }
}