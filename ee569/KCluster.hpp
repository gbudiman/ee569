//
//  KCluster.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/5/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef KCluster_hpp
#define KCluster_hpp

#include "main.hpp"
#include "Coordinate.hpp"

class KCluster {
public:
  KCluster(std::vector<std::pair<Coordinate, float>>, int, float);
  void categorize();
  
  int target_group;
  float deviation_step;
  std::vector<std::pair<Coordinate, float>> raw;
  std::vector<std::vector<std::pair<Coordinate, float>>> data;
  
private:
  void add(std::pair<Coordinate, float>, float);
  bool within_margin_at(int, float, float);
  float average_at(int);
  void debug();
};

#endif /* KCluster_hpp */
