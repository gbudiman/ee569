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
#include "KCluster.hpp"

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
  
  static int pseudo_group(int r, int c);
  void cluster_group_by_area();
  void cluster_group_by_roundness();
  void cluster_group_by_lightness();
  void cluster_group_by_location();
  void cluster_group_by_yellow_chroma();
  void cluster_group_by_red_chroma();
  
  void compute_average_size();
  void debug_sorted(std::vector<std::pair<int, float>>);
  
  void categorize_by_area();
private:
  std::vector<std::pair<int, float>> averaging_functor(std::vector<std::pair<int, float>>);
  void debug_combined(std::vector<std::vector<std::pair<Coordinate, float>>>);
  SpatialData find_by_coordinate(Coordinate);
  
  float area_multiplier;
  float length_multiplier;
  float roundness_multiplier;
};

#endif /* GrainCategorizer_hpp */
