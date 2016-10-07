//
//  Mpeg7Classifier.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/4/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
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
  vector<float> rating_diagonal = vector<float>();
  vector<float> rating_connectivity_two = vector<float>();
  vector<float> rating_branching_ratio = vector<float>();
  vector<float> rating_energy_concentration = vector<float>();
  vector<float> rating_protrusion = vector<float>();
  vector<float> rank = vector<float>(diagonal_lines.size() - 1);
  
  unsigned long comparator = diagonal_lines.size() - 1;
  for(int i = 0; i < diagonal_lines.size() - 1; i++) {
    
    
    rating_diagonal.push_back(compute_inverse_quadratic_difference(diagonal_lines.at(i).first + diagonal_lines.at(i).second, diagonal_lines.at(comparator).first + diagonal_lines.at(comparator).second));
    rating_connectivity_two.push_back(compute_inverse_quadratic_difference(connectivities.at(i).at(1), connectivities.at(comparator).at(1)) / 10000);
    rating_branching_ratio.push_back(compute_inverse_quadratic_difference(branching_ratio.at(i).first + branching_ratio.at(i).second, branching_ratio.at(comparator).first + branching_ratio.at(comparator).second) / 10000);
    rating_energy_concentration.push_back(compute_inverse_quadratic_difference(energy_concentration.at(i), energy_concentration.at(comparator)) / 10000);
    rating_protrusion.push_back(compute_inverse_quadratic_difference(protrusions.at(i), protrusions.at(comparator)));
  }
  
  printf(    "Method of classification              Image1  Image2   Weight  IW1     IW2\n");
  printf(    "-----------------------------------------------------------------------------\n");
  debug_rank("Template matching :: diagonal        ", rating_diagonal,             0.25, rank);
  debug_rank("Pixel with 2-connectivity            ", rating_connectivity_two,     0.25, rank);
  debug_rank("Distribution :: branching ratio      ", rating_branching_ratio,      0.1, rank);
  debug_rank("Distribution :: energy concentration ", rating_energy_concentration, 0.1, rank);
  debug_rank("Feature :: protrusions               ", rating_protrusion,           0.3, rank);
  printf(    "-----------------------------------------------------------------------------\n");
  printf(    "Cumulative Weighted Similarity ( 0 Different <---> 1 Similar ) ");
  for (auto i = rank.begin(); i != rank.end(); ++i) {
    printf("%5.4f  ", *i);
  }
  printf("\n");
}

void Mpeg7Classifier::debug_rank(const char* s, vector<float> data, float weight, vector<float>& rank) {
  printf("%s ", s);
  for (int i = 0; i < data.size(); i++) {
    printf("%5.4f  ", data.at(i));
  }
  
  printf(" | %2.0f%% | ", weight * 100);
  
  for (int i = 0; i < data.size(); i++) {
    printf("%5.4f  ", data.at(i) * weight);
    rank.at(i) += data.at(i) * weight;
  }
  
  printf("\n");
}

float Mpeg7Classifier::compute_inverse_quadratic_difference(float a, float b) {
  return 1 / ((b - a) * (b - a));
}

float Mpeg7Classifier::compute_quadratic_difference(float a, float b) {
  return (b - a) * (b - a);
}