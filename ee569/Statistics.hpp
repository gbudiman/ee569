//
//  Statistics.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/11/16.
//  Finalized on 10/31/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef Statistics_hpp
#define Statistics_hpp

#include "main.hpp"

class Statistics {
public:
  Statistics();
  void add_row(std::vector<float>);
  std::vector<float> compute_column_mean();
  std::vector<float> compute_column_variance();
  
  std::vector<std::vector<float>> data;
  std::vector<float> mean;
  std::vector<float> variance;
};

#endif /* Statistics_hpp */
