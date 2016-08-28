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
#include "CmykPixel.hpp"
#include "Histogram.hpp"

class Picture {
public:
  Picture(std::string, uint32_t, uint32_t, uint32_t);
  void write_to_file(std::string);
  void write_to_file(std::string, bool);
  void crop(uint32_t, uint32_t, uint32_t, uint32_t);
  void resize(uint32_t, uint32_t);

  void to_cmyk();
  void to_hsl();
  void debug_histogram();
private:
  void load();
  void load_rgb();
  void load_gray();
  
  void write_rgb(std::string);
  void write_cmyk(std::string);
  void write_hsl(std::string);
  
  void generate_histogram();
  
  RgbPixel bilinear_interpolate(float x, float y);
  
  std::string path;
  uint32_t dim_x;
  uint32_t dim_y;
  uint32_t type;
  std::vector<std::vector<RgbPixel>*>* data;
  std::vector<std::vector<RgbPixel>*>* result;
  std::vector<std::vector<CmykPixel>*>* data_cmyk;
  std::vector<std::vector<HslPixel>*>* data_hsl;
  
  std::vector<std::vector<uint8_t>*>* data_gray;
  std::vector<std::vector<uint8_t>*>* result_gray;
  
  Histogram *hist_r;
  Histogram *hist_g;
  Histogram *hist_b;
  Histogram *hist_gray;
};

#endif /* Picture_hpp */
