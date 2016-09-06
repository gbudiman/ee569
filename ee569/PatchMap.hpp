//
//  PatchMap.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef PatchMap_hpp
#define PatchMap_hpp

#include "main.hpp"
#include "RgbPixel.hpp"
#include "PatchCell.hpp"
#include "NlmWeight.hpp"

class PatchMap {
public:
  PatchMap(int, int, int, int, int, int, std::vector<std::vector<RgbPixel>*>*);
  std::vector<std::vector<RgbPixel>*>* picture_data;
  int dim_x;
  int dim_y;
  int patch_radius;
  RgbPixel* result;
  
  std::vector<std::vector<RgbPixel>> create_base_patch(int, int);
  int compute_patch_difference(std::vector<std::vector<RgbPixel>>, std::vector<std::vector<RgbPixel>>);
  
  ~PatchMap();
};



#endif /* PatchMap_hpp */
