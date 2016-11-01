//
//  FilterEnergy.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/13/16.
//  Finalized on 10/31/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef FilterEnergy_hpp
#define FilterEnergy_hpp

#include "main.hpp"

class FilterEnergy {
public:
  FilterEnergy();
  void add(std::vector<std::vector<float>>);
  void add(std::vector<std::vector<uint8_t>>*);
  void normalize();
  std::pair<float, float> min_max(int);
  
  cv::Mat generate_kmeans(int, int, int);
  std::vector<std::vector<uint8_t>> unwrap_kmeans(cv::Mat, int, int);
  
  std::vector<std::vector<std::vector<float>>> data;
private:
  void scale(int, float, float);
};

#endif /* FilterEnergy_hpp */
