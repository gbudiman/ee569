//
//  Picture.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef Picture_hpp
#define Picture_hpp

#include "main.hpp"
#include "RgbPixel.hpp"

class Picture {
public:
  Picture(std::string, uint32_t, uint32_t, uint32_t);
  void write_to_file(std::string);
  void crop(uint32_t, uint32_t, uint32_t, uint32_t);

private:
  void load();
  void load_rgb();
  
  void write_rgb(std::string);
  
  std::string path;
  uint32_t dim_x;
  uint32_t dim_y;
  uint32_t type;
  std::vector<std::vector<RgbPixel>*>* data;
  std::vector<std::vector<RgbPixel>*>* result;
};

#endif /* Picture_hpp */
