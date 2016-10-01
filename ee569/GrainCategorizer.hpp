//
//  GrainCategorizer.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/24/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef GrainCategorizer_hpp
#define GrainCategorizer_hpp

#include "main.hpp"
#include "Coordinate.hpp"
#include "SpatialData.hpp"
#include "BoundingBox.hpp"
#include "RgbPixel.hpp"

class GrainCategorizer {
public:
  GrainCategorizer();
  void add(int, int);
  int count_groups();
  void debug_groups();
  
  void insert_area_data(Coordinate, float);
  void correlate_chroma(Coordinate, RgbPixel);
  void correlate_length(BoundingBox, float);
  
  std::vector<std::vector<Coordinate>> grains;
  std::vector<SpatialData> grain_data;
  
  int pseudo_group(int r, int c);
private:
};

#endif /* GrainCategorizer_hpp */
