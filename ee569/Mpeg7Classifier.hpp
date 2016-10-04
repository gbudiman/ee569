//
//  Mpeg7Classifier.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/4/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef Mpeg7Classifier_hpp
#define Mpeg7Classifier_hpp

#include "main.hpp"

class Mpeg7Classifier {
public:
  Mpeg7Classifier();
  void classify_by_diagonal_lines(std::pair<int, int>);
  void classify_by_connectivities(std::vector<float>);
  void classify_by_branching_ratio(std::pair<float, float>);
  void classify_by_energy_concentration(float);
  void classify_by_protrusions(int);
  
  void rank_classficiation();
private:
  std::vector<std::pair<int, int>> diagonal_lines;
  std::vector<std::vector<float>> connectivities;
  std::vector<std::pair<float, float>> branching_ratio;
  std::vector<float> energy_concentration;
  std::vector<int> protrusions;
  
};
#endif /* Mpeg7Classifier_hpp */
