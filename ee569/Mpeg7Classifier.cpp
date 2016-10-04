//
//  Mpeg7Classifier.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/4/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Mpeg7Classifier.hpp"
using namespace std;

Mpeg7Classifier::Mpeg7Classifier() {
  vector<pair<int, int>> diagonal_lines = vector<pair<int, int>>();
  vector<vector<float>> connectivities = vector<vector<float>>();
  vector<pair<float, float>> branching_ratio = vector<pair<float, float>>();
  vector<float> energy_concentration = vector<float>();
  vector<int> protrusions = vector<int>();
}

void Mpeg7Classifier::classify_by_diagonal_lines(std::pair<int, int> p) {
  diagonal_lines.push_back(p);
}

void Mpeg7Classifier::classify_by_connectivities(std::vector<float> p) {
  connectivities.push_back(p);
}

void Mpeg7Classifier::classify_by_branching_ratio(std::pair<float, float> p) {
  branching_ratio.push_back(p);
}

void Mpeg7Classifier::classify_by_energy_concentration(float p) {
  energy_concentration.push_back(p);
}

void Mpeg7Classifier::classify_by_protrusions(int p) {
  protrusions.push_back(p);
}

void Mpeg7Classifier::rank_classficiation() {
  int z = 0;
}