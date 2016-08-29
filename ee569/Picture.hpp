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
  void prepare_gnuplot_histogram_data(std::string);
  void prepare_gnuplot_histogram_data(std::string, bool);
  void equalize(uint8_t);
  
  Histogram *hist_r;
  Histogram *hist_g;
  Histogram *hist_b;
  Histogram *cdf_r;
  Histogram *cdf_g;
  Histogram *cdf_b;
  
  Histogram *hist_gray;
  Histogram *cdf_gray;
private:
  void load();
  void load_rgb();
  void load_gray();
  
  void write_gray(std::string);
  void write_rgb(std::string);
  void write_cmyk(std::string);
  void write_hsl(std::string);
  
  void generate_histogram();
  
  void get_nonzero_cdf(uint8_t, uint8_t&, uint8_t&);
  void get_nonzero_pmf(uint8_t, uint8_t&, uint8_t&);
  std::vector<int16_t>* perform_equalization(uint8_t, uint8_t);
  void remap_histogram_gray(std::vector<int16_t>*);
  void remap_histogram_rgb(std::vector<int16_t>*, std::vector<int16_t>*, std::vector<int16_t>*);
  
  RgbPixel bilinear_interpolate(float x, float y);
  
  std::string path;
  uint32_t dim_x;
  uint32_t dim_y;
  uint32_t type;
  std::vector<std::vector<RgbPixel>*>* data;
  std::vector<std::vector<RgbPixel>*>* result;
  std::vector<std::vector<CmykPixel>*>* data_cmyk;
  std::vector<std::vector<HslPixel>*>* data_hsl;
  
  std::vector<std::vector<uint8_t>>* data_gray;
  std::vector<std::vector<uint8_t>>* result_gray;
};

#endif /* Picture_hpp */
