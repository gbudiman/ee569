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
#include "BinaryMatrix.hpp"
#include "GrainCategorizer.hpp"
#include "Coordinate.hpp"
#include "MorphMatrix.hpp"
#include "Tracer.hpp"
#include "BoundingBox.hpp"
#include "SpatialData.hpp"
#include "BoundaryTracer.hpp"

class Picture {
public:
  static Picture color_format_to_grayscale_raw(int, int, string);
  
  Picture();
  Picture(std::string, uint32_t, uint32_t, uint32_t);
  void copy_result_to_data();
  void copy_result_to_data(bool);
  void copy_data_to_result();
  void sum_result_and_data();
  float average_all_pixels();
  void subtract_average_to_laws_workspace();
  float average_laws_response(int);
  void normalize_laws_filter_response(int);
  pair<float, float> filter_response_peaks();
  vector<vector<float>> window_laws_response(int);
  void slurp(std::vector<std::vector<float>>);
  void slurp(std::vector<std::vector<uint8_t>>);
  void slurp(cv::Mat);
  void invert();

  void compare_f_measure(Picture, Picture, int&, int&, int&, int&);
  
  void write_to_file(std::string);
  void write_to_file(std::string, bool);
  void write_intermediate_mask_to_file(std::string);
  void write_separate_rgb_channel(std::string);
  void crop(uint32_t, uint32_t, uint32_t, uint32_t);
  void resize(uint32_t, uint32_t);
  
  void extend_boundary(int);
  
  bool set_compare(std::vector<Coordinate>, Coordinate);
  
  void to_cmyk();
  void to_hsl();
  void to_grayscale();
  void prepare_gnuplot_histogram_data(std::string);
  void prepare_gnuplot_histogram_data(std::string, bool);
  void prepare_gnuplot_transfer_function(std::string);
  void prepare_gnuplot_transfer_function(std::string, bool);
  
  cv::Mat to_cv2_mat();
  void slurp_cv2_mat(cv::Mat);
  void get_peak_hist(int, int);
  
  void equalize(uint8_t);
  void histogram_match_gray(Histogram*);
  void histogram_match_rgb(Histogram*, Histogram*, Histogram*);
  
  void assign_histogram(Histogram*, uint8_t, uint32_t, uint32_t);
  void apply_transfer_function_rgb(std::vector<int16_t>*, std::vector<int16_t>*, std::vector<int16_t>*);
  
  void apply_median_filter(uint32_t, uint32_t);
  void apply_mean_filter(uint32_t, uint32_t);
  void apply_gaussian_filter(int, float);
  void apply_nlm_filter(int, int, float);
  void apply_laws_filter(vector<float>, int);
  
  void diamond_warp();
  void find_piece(std::string, std::string);
  void find_hole(int*, int*, int*, int*);
  void fit_piece(Picture, int, int, int, int);
  void overlay_with(Picture);
  
  void dither(int);
  void dither_multi_level(int, int);
  
  void adaptive_thresholding();
  void adaptive_thresholding2(int);
  void morph(int);
  //void morph_thin();
  void morph_erode();
  vector<SpatialData> measure_area(std::vector<Coordinate>);
  vector<SpatialData> measure_length();
  vector<SpatialData> measure_chromaticity(Picture, std::vector<Coordinate>);
  void post_process_threshold();
  GrainCategorizer count_objects();
  std::vector<Coordinate> get_center_of_mass();
  
  std::vector<std::vector<Coordinate>> compute_spatial_data(GrainCategorizer);
  
  std::vector<Coordinate> trace_boundary();
  void fill_holes(std::vector<Coordinate>);
  void fill_holes2(std::vector<Coordinate>);
  
  void highlight_overlay(std::vector<std::vector<uint8_t>>*);
  
  std::pair<int, int> compute_diagonal_lines(int);
  vector<float> compute_global_connectivity();
  std::pair<float, float> compute_branching(int);
  float compute_concentration(int, float);
  
  int label_connected_components(int);
  
  void spp_cluster(int);
  
  uint32_t get_dim_x();
  uint32_t get_dim_y();
  uint32_t get_type();
  std::vector<std::vector<uint8_t>>* get_result_gray();
  std::vector<std::vector<uint8_t>>* get_data_gray();
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
  void load_binary();
  
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
  
  void initialize_result(uint8_t);
  void initialize_data(uint8_t);
  std::vector<int> extract_laws_workspace_unwrapped_matrix(int, int, int);
  std::vector<int> extract_laws_response_unwrapped_matrix(int, int, int);
  std::vector<uint8_t> extract_result_unwrapped_matrix(int, int, int);
  Matrix extract_matrix(int, int, int);
  Matrix extract_matrix(Coordinate, int);
  Matrix extract_mask(int, int, int);
  int extract_bitstream_matrix(int, int);
  
  int binary_delta();
  
  int expand_area(Coordinate, int, RgbPixel&);
  
  void dither_range_check(int, int, float, int);
  
  void scan_until_first_while_pixel(int&, int&);
  void scan_until_first_white_block(int&, int&);
  void scan_for_fillable_hole(int, int);
  void scan_until_hit_trace(uint32_t, int);
  bool hit_a_trace(uint32_t);
  bool has_been_visited(Coordinate);
  int determine_trace_direction(Coordinate, Coordinate);
  
  uint32_t compute_connectivity(int);
  
  uint32_t move(uint32_t, int);
  
  bool within_cluster_distance(std::vector<uint8_t>, int, int);
  
  std::string path;
  uint32_t dim_x;
  uint32_t dim_y;
  uint32_t type;
  std::vector<std::vector<RgbPixel>*>* data;
  std::vector<std::vector<RgbPixel>*>* result;
  std::vector<std::vector<CmykPixel>*>* data_cmyk;
  std::vector<std::vector<HslPixel>*>* data_hsl;
  
  std::vector<std::vector<uint8_t>>* data_gray;
  std::vector<std::vector<uint8_t>>* second_phase_gray;
  std::vector<std::vector<uint8_t>>* result_gray;
  std::vector<std::vector<int>>* laws_workspace;
  std::vector<std::vector<int>>* laws_response;
  std::vector<std::vector<uint8_t>>* windowed_laws_response;
  
  std::vector<int16_t> *tf_gray;
  std::vector<int16_t> *tf_red;
  std::vector<int16_t> *tf_green;
  std::vector<int16_t> *tf_blue;
  
//  vector<Coordinate> traces;
//  vector<Coordinate> visited_fill;
//  vector<Coordinate> queue;
  set<uint32_t> traces;
  set<uint32_t> visited_fill;
  set<uint32_t> queue;
  
  bool is_pseudo;
};

#endif /* Picture_hpp */
