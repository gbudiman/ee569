//
//  Picture.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef Picture_hpp
#define Picture_hpp

#include "main.hpp"
#include "RgbPixel.hpp"
#include "CmykPixel.hpp"
#include "Histogram.hpp"
#include "PatchMap.hpp"
#include "Kernel.hpp"
#include "Matrix.hpp"

class Picture {
public:
  Picture();
  Picture(std::string, uint32_t, uint32_t, uint32_t);
  void write_to_file(std::string);
  void write_to_file(std::string, bool);
  void write_separate_rgb_channel(std::string);
  void crop(uint32_t, uint32_t, uint32_t, uint32_t);
  void resize(uint32_t, uint32_t);

  void to_cmyk();
  void to_hsl();
  void prepare_gnuplot_histogram_data(std::string);
  void prepare_gnuplot_histogram_data(std::string, bool);
  void prepare_gnuplot_transfer_function(std::string);
  void prepare_gnuplot_transfer_function(std::string, bool);
  
  void equalize(uint8_t);
  void histogram_match_gray(Histogram*);
  void histogram_match_rgb(Histogram*, Histogram*, Histogram*);
  
  void assign_histogram(Histogram*, uint8_t, uint32_t, uint32_t);
  void apply_transfer_function_rgb(std::vector<int16_t>*, std::vector<int16_t>*, std::vector<int16_t>*);
  
  void apply_median_filter(uint32_t, uint32_t);
  void apply_mean_filter(uint32_t, uint32_t);
  void apply_gaussian_filter(int, float);
  void apply_nlm_filter(int, int, float);
  
  void diamond_warp();
  void find_piece(std::string, std::string);
  void find_hole(int*, int*, int*, int*);
  void fit_piece(Picture, int, int, int, int);
  
  void dither(int);
  void dither_multi_level(int);
  
  uint32_t get_dim_x();
  uint32_t get_dim_y();
  uint32_t get_type();
  std::vector<std::vector<RgbPixel>*>* get_rgb_data();
  
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
  void write_gray(std::string, std::vector<std::vector<uint8_t>*>*);
  void write_rgb(std::string);
  void write_cmyk(std::string);
  void write_hsl(std::string);
  
  void generate_histogram();
  void generate_cdf_from_histogram(uint8_t);
  
  void get_nonzero_cdf(uint8_t, uint8_t&, uint8_t&);
  void get_nonzero_pmf(uint8_t, uint8_t&, uint8_t&);
  std::vector<int16_t>* perform_equalization(uint8_t, uint8_t);
  void remap_histogram_gray(std::vector<int16_t>*);
  void remap_histogram_rgb(std::vector<int16_t>*, std::vector<int16_t>*, std::vector<int16_t>*);
  
  RgbPixel bilinear_interpolate(float x, float y);
  
  RgbPixel* create_kernel_and_overwrite_median(int, int, int, uint32_t);
  RgbPixel* create_kernel_and_overwrite_mean(int, int, int, uint32_t);
  
  std::vector<std::vector<uint8_t>> create_patch_matrix(int, int, int, int);
  
  void threaded_nlm_filter(int, int, std::vector<std::vector<RgbPixel>*>*, int, int, int);
  
  void dump_transfer_function(std::string, std::vector<int16_t>*);
  
  void remap_diamond_warp(int, int, int);
  
  void dither_2(std::vector<int>);
  void dither_4(std::vector<int>);
  void dither_4a(std::vector<int>);
  void dither_8(std::vector<int>);
  void dither_fsb();
  void dither_jjn();
  void dither_stucki();
  void apply_dithering(Matrix, std::vector<int>);
  
  int find_closest_palette(float, std::vector<int>);
  
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
  
  std::vector<int16_t> *tf_gray;
  std::vector<int16_t> *tf_red;
  std::vector<int16_t> *tf_green;
  std::vector<int16_t> *tf_blue;
  
  bool is_pseudo;
};

#endif /* Picture_hpp */
