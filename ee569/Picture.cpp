//
//  Picture.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Picture.hpp"
using namespace std;

Picture::Picture() {
  is_pseudo = true;
}

Picture::Picture(string _path, uint32_t _dim_x, uint32_t _dim_y, uint32_t _type) {
  is_pseudo = false;
  path = _path;
  dim_x = _dim_x;
  dim_y = _dim_y;
  type = _type;
  
  load();
  generate_histogram();
}

void Picture::write_to_file(string _path) {
  switch(type) {
    case COLOR_GRAY: write_gray(_path); break;
    case COLOR_RGB: write_rgb(_path); break;
    case COLOR_CMYK: write_cmyk(_path); break;
    case COLOR_HSL: write_hsl(_path); break;
  }
}

void Picture::write_to_file(string _path, bool strip_extension) {
  // strip extension will remove the extension
  // thus making it possible to append anything before the extension
  // the extension must be added back and it's the caller's responsibility to do so
  
  if (strip_extension) {
    uint32_t dot_position = (uint32_t) _path.find_last_of('.');
    write_to_file(_path.substr(0, dot_position));
  } else {
    write_to_file(_path);
  }
}

void Picture::write_separate_rgb_channel(string _path) {
  if (type != COLOR_RGB) {
    cout << "ERROR: RGB channel separation can only be done on COLOR_RGB Picture" << "\n";
  }
  
  uint32_t dot_position = (uint32_t) _path.find_last_of('.');
  string base_path = _path.substr(0, dot_position);
  string out_red = base_path + "_channel_red.raw";
  string out_green = base_path + "_channel_green.raw";
  string out_blue = base_path + "_channel_blue.raw";
  vector<vector<uint8_t>*>* split_red = new vector<vector<uint8_t>*>();
  vector<vector<uint8_t>*>* split_green = new vector<vector<uint8_t>*>();
  vector<vector<uint8_t>*>* split_blue = new vector<vector<uint8_t>*>();
  
  for (uint32_t r = 0; r < data->size(); r++) {
    vector<uint8_t> *row_data_red = new vector<uint8_t>();
    vector<uint8_t> *row_data_green = new vector<uint8_t>();
    vector<uint8_t> *row_data_blue = new vector<uint8_t>();
    
    for (uint32_t c = 0; c < data->at(r)->size(); c++) {
      row_data_red->push_back(data->at(r)->at(c).r);
      row_data_green->push_back(data->at(r)->at(c).g);
      row_data_blue->push_back(data->at(r)->at(c).b);
    }
    
    split_red->push_back(row_data_red);
    split_green->push_back(row_data_green);
    split_blue->push_back(row_data_blue);
  }
  
  write_gray(out_red, split_red);
  write_gray(out_green, split_green);
  write_gray(out_blue, split_blue);
}

void Picture::prepare_gnuplot_transfer_function(string out_path) {
  // Dump raw data for plotting transfer function
  
  string out_gray_tf = out_path + "_tf_gray.txt";
  string out_red_tf = out_path + "_tf_red.txt";
  string out_green_tf = out_path + "_tf_green.txt";
  string out_blue_tf = out_path + "_tf_blue.txt";
  
  switch (type) {
    case COLOR_GRAY:
      dump_transfer_function(out_gray_tf, tf_gray);
      break;
    case COLOR_RGB:
      dump_transfer_function(out_red_tf, tf_red);
      dump_transfer_function(out_green_tf, tf_green);
      dump_transfer_function(out_blue_tf, tf_blue);
      break;
  }
}

void Picture::dump_transfer_function(string out_path, vector<int16_t> *data) {
  ofstream osmulti;
  uint8_t state = 0;
  
  osmulti.open(out_path, ios::out);
  for (int i = 0; i < data->size(); i++) {
    if (data->at(i) >= 0 && data->at(i) < 256) {
      if (state == 0 && data->at(i) >= 0) {
        state = 1;
      }
      
      osmulti << data->at(i);
    } else {
      if (state == 1) {
        osmulti << 255;
      } else {
        osmulti << 0;
      }
    }
    
    osmulti << "\n";
  }
  osmulti.close();
}

void Picture::prepare_gnuplot_histogram_data(string out_path) {
  // Dump raw data for CDF/PDF histogram plotting
  
  string out_gray_pdf = out_path + "_hist_gray_pdf.txt";
  string out_gray_cdf = out_path + "_hist_gray_cdf.txt";
  
  string out_red_pdf = out_path + "_hist_red_pdf.txt";
  string out_red_cdf = out_path + "_hist_red_cdf.txt";
  string out_green_pdf = out_path + "_hist_green_pdf.txt";
  string out_green_cdf = out_path + "_hist_green_cdf.txt";
  string out_blue_pdf = out_path + "_hist_blue_pdf.txt";
  string out_blue_cdf = out_path + "_hist_blue_cdf.txt";
  
  ofstream osgp, osgc;
  ofstream oscrp, oscrc,
           oscgp, oscgc,
           oscbp, oscbc;
  
  switch(type) {
    case COLOR_GRAY:
      osgp.open(out_gray_pdf, ios::out);
      osgc.open(out_gray_cdf, ios::out);
      
      for (int i = 0; i < hist_gray->data->size(); i++) {
        osgp << hist_gray->data->at(i) << "\n";
        osgc << cdf_gray->data->at(i) << "\n";
      }
      
      osgp.close();
      osgc.close();
      break;
    case COLOR_RGB:
      oscrp.open(out_red_pdf, ios::out);
      oscrc.open(out_red_cdf, ios::out);
      oscgp.open(out_green_pdf, ios::out);
      oscgc.open(out_green_cdf, ios::out);
      oscbp.open(out_blue_pdf, ios::out);
      oscbc.open(out_blue_cdf, ios::out);
      
      for (int i = 0; i < hist_r->data->size(); i++) {
        oscrp << hist_r->data->at(i) << "\n";
        oscrc << cdf_r->data->at(i) << "\n";
        oscgp << hist_g->data->at(i) << "\n";
        oscgc << cdf_g->data->at(i) << "\n";
        oscbp << hist_b->data->at(i) << "\n";
        oscbc << cdf_b->data->at(i) << "\n";
      }
      
      oscrp.close();
      oscrc.close();
      oscgp.close();
      oscgc.close();
      oscbp.close();
      oscbc.close();
      break;
  }
}

void Picture::prepare_gnuplot_histogram_data(string path, bool strip_extension) {
  if (strip_extension) {
    uint32_t dot_position = (uint32_t) path.find_last_of('.');
    prepare_gnuplot_histogram_data(path.substr(0, dot_position));
  } else {
    prepare_gnuplot_histogram_data(path);
  }
}

void Picture::prepare_gnuplot_transfer_function(string path, bool strip_extension) {
  if (strip_extension) {
    uint32_t dot_position = (uint32_t) path.find_last_of('.');
    prepare_gnuplot_transfer_function(path.substr(0, dot_position));
  } else {
    prepare_gnuplot_transfer_function(path);
  }
}

void Picture::load() {
  switch(type) {
    case COLOR_RGB: load_rgb(); break;
    case COLOR_GRAY: load_gray(); break;
  }
}

void Picture::assign_histogram(Histogram *h, uint8_t hist_type, uint32_t x, uint32_t y) {
  if (hist_type == CHANNEL_GRAY) {
    type = COLOR_GRAY;
  } else {
    type = COLOR_RGB;
  }
  
  dim_x = x;
  dim_y = y;
  
  switch(hist_type) {
    case CHANNEL_GRAY:
      hist_gray = h;
      cdf_gray = new Histogram();
      generate_cdf_from_histogram(CHANNEL_GRAY);
      break;
    case CHANNEL_RED:
      hist_r = h;
      cdf_r = new Histogram();
      generate_cdf_from_histogram(CHANNEL_RED);
      break;
    case CHANNEL_GREEN:
      hist_g = h;
      cdf_g = new Histogram();
      generate_cdf_from_histogram(CHANNEL_GREEN);
      break;
    case CHANNEL_BLUE:
      hist_b = h;
      cdf_b = new Histogram();
      generate_cdf_from_histogram(CHANNEL_BLUE);
      break;
  }
}

void Picture::generate_cdf_from_histogram(uint8_t channel) {
  uint32_t cdf = 0;
  Histogram *multi = hist_gray;
  Histogram *cdfm = cdf_gray;
  switch (channel) {
    case CHANNEL_RED:
      multi = hist_r;
      cdfm = cdf_r;
      break;
    case CHANNEL_GREEN:
      multi = hist_g;
      cdfm = cdf_g;
      break;
    case CHANNEL_BLUE:
      multi = hist_b;
      cdfm = cdf_b;
      break;
  }
  
  for (auto i = 0; i != multi->data->size(); i++) {
    cdf += multi->data->at(i);
    cdfm->data->at(i) = cdf;
  }
}

void Picture::generate_histogram() {
  uint32_t cdf_value = 0;
  uint32_t cdf_red = 0;
  uint32_t cdf_green = 0;
  uint32_t cdf_blue = 0;
  
  uint32_t pixel_count = 0;
  
  switch(type) {
    case COLOR_GRAY:
      hist_gray = new Histogram();
      cdf_gray = new Histogram();
      
      for (auto r = data_gray->begin(); r != data_gray->end(); ++r) {
        for (auto c = r->begin(); c != r->end(); ++c) {
          hist_gray->push(*c);
          pixel_count++;
        }
      }
      
      cdf_value = 0;
      for (auto i = 0; i < hist_gray->data->size(); i++) {
        cdf_value += hist_gray->data->at(i);
        cdf_gray->update_at(i, cdf_value);
      }
      break;
      
    case COLOR_RGB:
      hist_r = new Histogram();
      hist_g = new Histogram();
      hist_b = new Histogram();
      cdf_r = new Histogram();
      cdf_g = new Histogram();
      cdf_b = new Histogram();
      
      cdf_red = cdf_green = cdf_blue = 0;
      
      for (auto r = data->begin(); r != data->end(); ++r) {
        for (auto c = (*r)->begin(); c != (*r)->end(); ++c) {
          
          hist_r->push(c->r);
          hist_g->push(c->g);
          hist_b->push(c->b);
        }
      }
      
      for (auto i = 0; i < hist_r->data->size(); i++) {
        cdf_red += hist_r->data->at(i);
        cdf_green += hist_g->data->at(i);
        cdf_blue += hist_b->data->at(i);
        
        cdf_r->update_at(i, cdf_red);
        cdf_g->update_at(i, cdf_green);
        cdf_b->update_at(i, cdf_blue);
      }
      break;
  }
}

void Picture::crop(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
  result = new std::vector<std::vector<RgbPixel>*>();
  std::vector<RgbPixel>* row_data;
  
  for (uint32_t y = y1; y <= y2; y++) {
    row_data = new std::vector<RgbPixel>();
    
    for (uint32_t x = x1; x <= x2; x++) {
      row_data->push_back(data->at(y)->at(x));
    }
    
    result->push_back(row_data);
  }
}

void Picture::resize(uint32_t _x, uint32_t _y) {
  uint32_t origin_max_x = dim_x - 1;
  uint32_t origin_max_y = dim_y - 1;
  
  uint32_t target_max_x = _x - 1;
  uint32_t target_max_y = _y - 1;
  
  float gradient_x = (float) origin_max_x / (float) target_max_x;
  float gradient_y = (float) origin_max_y / (float) target_max_y;
  
  result = new std::vector<std::vector<RgbPixel>*>();
  std::vector<RgbPixel>* row_data;
  
  for (uint32_t y = 0; y < _y; y++) {
    row_data = new std::vector<RgbPixel>();
    
    float interp_y = gradient_y * y;
    for (uint32_t x = 0; x < _x; x++) {
      float interp_x = gradient_x * x;
      
      RgbPixel interpolated_pixel = bilinear_interpolate(interp_x, interp_y);
      row_data->push_back(interpolated_pixel);
//      if (HEAVY_DEBUG) {
//        printf("(%.3d, %.3d) -> (%.2f, %.2f) | [%.2f %.2f][%.2f %.2f]\n", x, y, interp_x, interp_y, floor(interp_x), ceil(interp_x), floor(interp_y), ceil(interp_y));
//      }
    }
    
    result->push_back(row_data);
  }
}

RgbPixel Picture::bilinear_interpolate(float x, float y) {
  bool x_exact = false;
  float x_floor = floor(x);
  float x_ceil = ceil(x);
//  float x_left;
//  float x_right;
  float x_val = 0;
  
  bool y_exact = false;
  float y_floor = floor(y);
  float y_ceil = ceil(y);
//  float y_left;
//  float y_right;
  float y_val = 0;
  
  // Case 1: X is whole-integer
  if (x_floor == x_ceil) {
    x_exact = true;
    if (x_floor == 0) {
      x_val = 0;
    } else {
      x_val = x_floor;
    }
  } else {
//    x_left = x - x_floor;
//    x_right = x_ceil - x;
  }
  
  // Case 2: Y is whole-integer
  if (y_floor == y_ceil) {
    y_exact = true;
    if (y_floor == 0) {
      y_val = 0;
    } else {
      y_val = y_floor;
    }
  } else {
//    y_left = y - y_floor;
//    y_right = y_ceil - y;
  }
  
  // Case 3: Both X and Y are whole-integer
  if (x_exact && y_exact) {
    if (HEAVY_DEBUG) {
      printf("[X] [Y](% 7.2f, % 7.2f) -> (% 7.2f, % 7.2f)\n", x, y, x_val, y_val);
    }
    
    return data->at(y_val)->at(x_val);
  } else {
    uint32_t cr, cb, cg;
    if (x_exact) {
      if (HEAVY_DEBUG) {
        printf("[X] [ ](% 7.2f, % 7.2f) -> (% 7.2f, % 7.2f)(% 7.2f, % 7.2f)\n", x, y, x_val, y_floor, x_val, y_ceil);
      }
      
      RgbPixel a = data->at(y_floor)->at(x_val);
      RgbPixel b = data->at(y_ceil)->at(x_val);
      
      cr = ((uint32_t) a.r + (uint32_t) b.r) / 2;
      cg = ((uint32_t) a.g + (uint32_t) b.g) / 2;
      cb = ((uint32_t) a.b + (uint32_t) b.b) / 2;
    } else if (y_exact) {
      if (HEAVY_DEBUG) {
        printf("[ ] [Y](% 7.2f, % 7.2f) -> (% 7.2f, % 7.2f)(% 7.2f, % 7.2f)\n", x, y, x_floor, y_val, x_ceil, y_val);
      }
      
      RgbPixel a = data->at(y_val)->at(x_floor);
      RgbPixel b = data->at(y_val)->at(x_ceil);
      
      cr = ((uint32_t) a.r + (uint32_t) b.r) / 2;
      cg = ((uint32_t) a.g + (uint32_t) b.g) / 2;
      cb = ((uint32_t) a.b + (uint32_t) b.b) / 2;
    } else {
      // Implicit case 4 where neither X nor Y are whole-integer
      
      if (HEAVY_DEBUG) {
        printf("(% 7.2f, % 7.2f) -> (% 7.2f, % 7.2f)(% 7.2f, % 7.2f)(% 7.2f, % 7.2f)(% 7.2f, % 7.2f)\n", x, y, x_floor, y_floor, x_floor, y_ceil, x_ceil, y_floor, x_ceil, y_ceil);
      }
      
      RgbPixel a = data->at(y_floor)->at(x_floor);
      RgbPixel b = data->at(y_ceil)->at(x_floor);
      RgbPixel c = data->at(y_floor)->at(x_ceil);
      RgbPixel d = data->at(y_ceil)->at(x_ceil);
      
      cr = ((uint32_t) a.r + (uint32_t) b.r + (uint32_t) c.r + (uint32_t) d.r) / 4;
      cg = ((uint32_t) a.g + (uint32_t) b.g + (uint32_t) c.g + (uint32_t) d.g) / 4;
      cb = ((uint32_t) a.b + (uint32_t) b.b + (uint32_t) c.b + (uint32_t) d.b) / 4;
    }
    
    return RgbPixel(cr, cg, cb);
  }
}

void Picture::equalize(uint8_t method) {  
  switch(type) {
    case COLOR_GRAY:
      //get_nonzero_cdf(CHANNEL_GRAY, nzcdf_gray_lo, nzcdf_gray_hi);
      tf_gray = perform_equalization(CHANNEL_GRAY, method);
      
      if (is_pseudo) {
      } else {
        remap_histogram_gray(tf_gray);
      }
      
      break;
    case COLOR_RGB:
      tf_red = perform_equalization(CHANNEL_RED, method);
      tf_green = perform_equalization(CHANNEL_GREEN, method);
      tf_blue = perform_equalization(CHANNEL_BLUE, method);
      
      if (is_pseudo) {
      } else {
        remap_histogram_rgb(tf_red, tf_green, tf_blue);
      }
      
      break;
  }
}

void Picture::get_nonzero_cdf(uint8_t channel, uint8_t &lo, uint8_t &hi) {
  Histogram *q;
  uint8_t state = 0;
  uint32_t max_cdf = dim_x * dim_y;
  uint32_t min_cdf = 0xFFFFFFFF;
  
  switch(channel) {
    case CHANNEL_RED:   q = cdf_r; break;
    case CHANNEL_GREEN: q = cdf_g; break;
    case CHANNEL_BLUE:  q = cdf_b; break;
    default:            q = cdf_gray;
  }
  
  for (auto i = 0; i < q->data->size(); i++) {
    auto current_data = q->data->at(i);
    
    if (current_data > 0) {
      lo = current_data;
      break;
    }
  }
}

void Picture::get_nonzero_pmf(uint8_t channel, uint8_t &lo, uint8_t &hi) {
  Histogram *q;
  uint8_t state = 0;
  uint32_t max_cdf = dim_x * dim_y;
  uint32_t min_cdf = 0xFFFFFFFF;
  
  switch(channel) {
    case CHANNEL_RED:   q = cdf_r; break;
    case CHANNEL_GREEN: q = cdf_g; break;
    case CHANNEL_BLUE:  q = cdf_b; break;
    default:            q = cdf_gray;
  }
  
  for (auto i = 0; i < q->data->size(); i++) {
    auto current_data = q->data->at(i);
    
    if (state == 0 && current_data > 0) {
      state = 1;
      lo = i;
    } else if (state == 1 && current_data == max_cdf) {
      hi = i;
      state = 2;
    }
  }
}

RgbPixel* Picture::create_kernel_and_overwrite_median(int kernel_size, int center_r, int center_c, uint32_t channel_mask) {
  vector<vector<RgbPixel>*> *kernel = new vector<vector<RgbPixel>*>();
  int pos_r = 0;
  int pos_c = 0;
  
  int x_spread = (int) dim_x;
  int y_spread = (int) dim_y;
  
  for (int r = center_r - kernel_size/2; r <= center_r + kernel_size/2; r++) {
    vector<RgbPixel> *row_data = new vector<RgbPixel>();
    if (r >= y_spread) {
      uint32_t y_limit = y_spread - 1;
      uint32_t overshoot = r - y_limit;
      pos_r = y_limit - overshoot;
    } else {
      pos_r = abs(r);
    }
    
    for (int c = center_c - kernel_size/2; c <= center_c + kernel_size/2; c++) {
      if (c >= x_spread) {
        uint32_t x_limit = x_spread - 1;
        uint32_t overshoot = c - x_limit;
        pos_c = x_limit - overshoot;
      } else {
        pos_c = abs(c);
      }
      
      //cout << "== " << pos_r << ", " << pos_c << "\n";
      row_data->push_back(data->at(pos_r)->at(pos_c));
    }
    
    kernel->push_back(row_data);
  }
  
  vector<uint8_t> *flattened_r = new vector<uint8_t>();
  vector<uint8_t> *flattened_g = new vector<uint8_t>();
  vector<uint8_t> *flattened_b = new vector<uint8_t>();
  
  for (auto i = 0; i < kernel->size(); i++) {
    for (auto j = 0; j < kernel->at(i)->size(); j++) {
      flattened_r->push_back(kernel->at(i)->at(j).r);
      flattened_g->push_back(kernel->at(i)->at(j).g);
      flattened_b->push_back(kernel->at(i)->at(j).b);
    }
  }
  
  sort(flattened_r->begin(), flattened_r->begin() + pow(kernel_size, 2));
  sort(flattened_g->begin(), flattened_g->begin() + pow(kernel_size, 2));
  sort(flattened_b->begin(), flattened_b->begin() + pow(kernel_size, 2));
  int midpoint = pow(kernel_size, 2) / 2;
  
  uint8_t medianed_r = ((channel_mask & FILTER_RED) == FILTER_RED) ? flattened_r->at(midpoint) : data->at(center_r)->at(center_c).r;
  uint8_t medianed_g = ((channel_mask & FILTER_GREEN) == FILTER_GREEN) ? flattened_g->at(midpoint) : data->at(center_r)->at(center_c).g;
  uint8_t medianed_b = ((channel_mask & FILTER_BLUE) == FILTER_BLUE) ? flattened_b->at(midpoint) : data->at(center_r)->at(center_c).b;
  RgbPixel *medianed = new RgbPixel(medianed_r, medianed_g, medianed_b);
  
  if (HEAVY_DEBUG) {
    int s = pow(kernel_size, 2);
    for (int i = 0; i < s; i++) {
      printf("%d ", flattened_r->at(i));
    }
    printf("\n");
    for (int i = 0; i < s; i++) {
      printf("%d ", flattened_g->at(i));
    }
    printf("\n");
    for (int i = 0; i < s; i++) {
      printf("%d ", flattened_b->at(i));
    }
    printf("\n");

    cout << "-->" << (int) medianed_r << "," << (int) medianed_g << "," << (int) medianed_b << endl;
  }
  
  return medianed;
}

RgbPixel* Picture::create_kernel_and_overwrite_mean(int kernel_size, int center_r, int center_c, uint32_t channel_mask) {
  vector<vector<RgbPixel>*> *kernel = new vector<vector<RgbPixel>*>();
  int pos_r = 0;
  int pos_c = 0;
  
  int x_spread = (int) dim_x;
  int y_spread = (int) dim_y;
  
  for (int r = center_r - kernel_size/2; r <= center_r + kernel_size/2; r++) {
    vector<RgbPixel> *row_data = new vector<RgbPixel>();
    if (r >= y_spread) {
      uint32_t y_limit = y_spread - 1;
      uint32_t overshoot = r - y_limit;
      pos_r = y_limit - overshoot;
    } else {
      pos_r = abs(r);
    }
    
    for (int c = center_c - kernel_size/2; c <= center_c + kernel_size/2; c++) {
      if (c >= x_spread) {
        uint32_t x_limit = x_spread - 1;
        uint32_t overshoot = c - x_limit;
        pos_c = x_limit - overshoot;
      } else {
        pos_c = abs(c);
      }
      
      //cout << "== " << pos_r << ", " << pos_c << "\n";
      row_data->push_back(data->at(pos_r)->at(pos_c));
    }
    
    kernel->push_back(row_data);
  }
  
  uint32_t sum_r = 0;
  uint32_t sum_g = 0;
  uint32_t sum_b = 0;
  uint32_t div = kernel->size() * kernel->size();
  
  for (auto i = 0; i < kernel->size(); i++) {
    for (auto j = 0; j < kernel->at(i)->size(); j++) {
      sum_r += kernel->at(i)->at(j).r;
      sum_g += kernel->at(i)->at(j).g;
      sum_b += kernel->at(i)->at(j).b;
    }
  }
  
  uint8_t mean_r = ((channel_mask & FILTER_RED) == FILTER_RED) ? sum_r / div : data->at(center_r)->at(center_c).r;
  uint8_t mean_g = ((channel_mask & FILTER_GREEN) == FILTER_GREEN) ? sum_g / div : data->at(center_r)->at(center_c).g;
  uint8_t mean_b = ((channel_mask & FILTER_BLUE) == FILTER_BLUE) ? sum_b / div : data->at(center_r)->at(center_c).b;
  RgbPixel *meaned = new RgbPixel(mean_r, mean_g, mean_b);
  
  return meaned;
}


std::vector<int16_t>* Picture::perform_equalization(uint8_t channel, uint8_t method) {
  std::vector<int16_t> *eqlz_map = new std::vector<int16_t>(256);
  uint8_t nzcdf_lo, nzcdf_hi = 0;
  
  
  for (auto i = eqlz_map->begin(); i < eqlz_map->end(); i++) {
    *i = -1;
  }
  Histogram *multi = cdf_gray;
  
  //cout << "CDF channel " << channel << ": " << (uint32_t) nzcdf_lo << " -> " << (uint32_t) nzcdf_hi << "\n";
  switch (channel) {
    case CHANNEL_RED:    multi = cdf_r; break;
    case CHANNEL_GREEN:  multi = cdf_g; break;
    case CHANNEL_BLUE:   multi = cdf_b; break;
  }
  
  if (method == EQUALIZE_CDF) {
    get_nonzero_cdf(channel, nzcdf_lo, nzcdf_hi);
    for (int i = 0; i < 256; i++) {
      uint16_t res = 0;
      //uint32_t res = ((float) (cdf_gray->data->at(i) - nzcdf_lo) / (float) (dim_x * dim_y - nzcdf_lo) * (256 - 2)) + 1;
      
      res = (int16_t) ((float) (multi->data->at(i) - nzcdf_lo) / (float) (dim_x * dim_y - nzcdf_lo) * (256 - 2)) + 1;
      eqlz_map->at(i) = res;
    }
  } else if (method == EQUALIZE_LINEAR) {
    get_nonzero_pmf(channel, nzcdf_lo, nzcdf_hi);
    cout << "Linear equalization of " << (uint32_t) nzcdf_lo << " to " << (uint32_t) nzcdf_hi << "\n";
    for (uint16_t i = nzcdf_lo; i <= nzcdf_hi; i++) {
      //int16_t new_index = (int16_t) ((float) i * (float) 255 / (nzcdf_hi - nzcdf_lo + 1) - (nzcdf_hi - nzcdf_lo));
      int16_t new_index = (float) 255 / (float) (nzcdf_hi - nzcdf_lo + 1) * (float) (i - nzcdf_lo);
      eqlz_map->at(i) = new_index;
    }
  }
  
  if (HEAVY_DEBUG) {
    for (uint32_t i = 0; i < eqlz_map->size(); i++) {
      printf("%d -> %X\n", i, (int16_t) eqlz_map->at(i));
    }
  }
  
  return eqlz_map;
}

void Picture::apply_transfer_function_rgb(vector<int16_t> *l_r, vector<int16_t> *l_g, vector<int16_t> *l_b) {
  tf_red = l_r;
  tf_green = l_g;
  tf_blue = l_b;
  
  remap_histogram_rgb(tf_red, tf_green, tf_blue);
}

void Picture::apply_nlm_filter(int search_radius, int patch_radius, float decay_factor) {
  result = new vector<vector<RgbPixel>*>();
  
//  int threads_available = thread::hardware_concurrency();
//  int work_chunk = dim_y /threads_available;
//  thread *tt = new thread[threads_available];
//  vector<vector<RgbPixel>*>* result_thread = new vector<vector<RgbPixel>*>(threads_available);
//  
//  printf("%d threads available\n", threads_available);
//  
//  for (int t = 0; t < threads_available; t++) {
//    int lower_limit = t * work_chunk;
//    int upper_limit = (t + 1) * work_chunk > dim_y ? dim_y : (t + 1) * work_chunk;
//    
//    thread (&Picture::threaded_nlm_filter, lower_limit, upper_limit, ref(result_thread->at(t)), t, search_radius, patch_radius);
//  }
//  
//  for (int t = 0; t < threads_available; t++) {
//    tt[t].join();
//  }
//  
//  printf("All threads joined\n");
  
  // non-threading impelemntation
  for (int r = 0; r < dim_y; r++) {
    vector<RgbPixel>* row_data = new vector<RgbPixel>();
    
    printf("Computing row %d\n", r);
    for (int c = 0; c < dim_x; c++) {
      
      PatchMap pm = PatchMap(r, c, dim_x, dim_y, search_radius, patch_radius, data, decay_factor);
      row_data->push_back(*pm.result);
    }
    
    result->push_back(row_data);
  }
  // end non-threading implementation
}

// NO!!!
//void Picture::threaded_nlm_filter(int lower_limit, int upper_limit, vector<vector<RgbPixel>*>* temp, int thread_id, int search_radius, int patch_radius) {
//  for (int r = lower_limit; r < upper_limit; r++) {
//    vector<RgbPixel>* row_data = new vector<RgbPixel>();
//    
//    printf("Thread %d computing row %d\n", thread_id, r);
//    for (int c = 0; c < dim_x; c++) {
//      PatchMap *pm = new PatchMap(r, c, dim_x, dim_y, search_radius, patch_radius, data);
//      row_data->push_back(*pm->result);
//    }
//    
//    temp->push_back(row_data);
//  }
//}

void Picture::remap_histogram_gray(std::vector<int16_t> *luteq) {
  // Use provided equalization table to re-map values
  
  result_gray = new vector<vector<uint8_t>>();
  
  for (auto r = data_gray->begin(); r != data_gray->end(); ++r) {
    vector<uint8_t> row_data = *new vector<uint8_t>();
    
    for (auto c = r->begin(); c != r->end(); ++c) {
      int16_t mapped_value = luteq->at(*c);
      //printf("%d -> %d\n", *c, mapped_value);
      row_data.push_back((uint8_t) mapped_value);
    }
    
    result_gray->push_back(row_data);
  }
}

void Picture::apply_gaussian_filter(int radius, float sigma) {
  Kernel k = Kernel(radius, sigma);
  result = new vector<vector<RgbPixel>*>();
  
  vector<vector<uint8_t>> mat_r = vector<vector<uint8_t>>();
  vector<vector<uint8_t>> mat_g = vector<vector<uint8_t>>();
  vector<vector<uint8_t>> mat_b = vector<vector<uint8_t>>();
  
  for (uint32_t r = 0; r < dim_y; r++) {
    vector<RgbPixel> *row_data = new vector<RgbPixel>();

    for (uint32_t c = 0; c < dim_x; c++) {
      mat_r = create_patch_matrix(r, c, radius, CHANNEL_RED);
      mat_g = create_patch_matrix(r, c, radius, CHANNEL_GREEN);
      mat_b = create_patch_matrix(r, c, radius, CHANNEL_BLUE);
      
      k.convolve(mat_r);
      k.convolve(mat_g);
      k.convolve(mat_b);
      
      RgbPixel p = RgbPixel(k.convolve(mat_r), k.convolve(mat_g), k.convolve(mat_b));
      row_data->push_back(p);
    }
    
    result->push_back(row_data);
  }
}

vector<vector<uint8_t>> Picture::create_patch_matrix(int r, int c, int radius, int channel) {
  vector<vector<uint8_t>> result = vector<vector<uint8_t>>();
  int pos_r, pos_c = 0;
  int i_dim_x = (int) dim_x;
  int i_dim_y = (int) dim_y;
  
  for (int rr = r - radius; rr <= r + radius; rr++) {
    vector<uint8_t> row_data = vector<uint8_t>();
    
    // Handle edge cases
    // img[-1] == img[1], img[-2] == img[2] so on
    if (rr >= i_dim_y) {
      int y_limit = i_dim_y - 1;
      int overshoot = rr - y_limit;
      pos_r = y_limit - overshoot;
    } else {
      pos_r = abs(rr);
    }
    
    for (int cc = c - radius; cc <= c + radius; cc++) {
      if (cc >= i_dim_x) {
        int x_limit = i_dim_x - 1;
        int overshoot = cc - x_limit;
        pos_c = x_limit - overshoot;
      } else {
        pos_c = abs(cc);
      }
      
      switch(channel) {
        case CHANNEL_RED: row_data.push_back(data->at(pos_r)->at(pos_c).r); break;
        case CHANNEL_GREEN: row_data.push_back(data->at(pos_r)->at(pos_c).g); break;
        case CHANNEL_BLUE: row_data.push_back(data->at(pos_r)->at(pos_c).b); break;
      }
    }
    
    result.push_back(row_data);
  }
  
  return result;
}

void Picture::apply_median_filter(uint32_t filter_size, uint32_t channel_mask) {
  result = new vector<vector<RgbPixel>*>();
  
  for (uint32_t r = 0; r < dim_y; r++) {
    vector<RgbPixel> *row_data = new vector<RgbPixel>();

    for (uint32_t c = 0; c < dim_x; c++) {
      //cout << r << ", " << c << "\n";
      row_data->push_back(*create_kernel_and_overwrite_median(filter_size, r, c, channel_mask));
    }
    
    result->push_back(row_data);
  }
}

void Picture::apply_mean_filter(uint32_t filter_size, uint32_t channel_mask) {
  result = new vector<vector<RgbPixel>*>();
  
  for (uint32_t r = 0; r < dim_y; r++) {
    vector<RgbPixel> *row_data = new vector<RgbPixel>();
    
    for (uint32_t c = 0; c < dim_x; c++) {
      row_data->push_back(*create_kernel_and_overwrite_mean(filter_size, r, c, channel_mask));
    }
    
    result->push_back(row_data);
  }
}

void Picture::remap_histogram_rgb(std::vector<int16_t> *l_r, std::vector<int16_t> *l_g, std::vector<int16_t> *l_b) {
  result = new vector<vector<RgbPixel>*>();
  
  for (uint32_t r = 0; r < data->size(); r++) {
    vector<RgbPixel>* row_data = new vector<RgbPixel>();
    
    for (uint32_t c = 0; c < data->at(r)->size(); c++) {
      RgbPixel pre_value = data->at(r)->at(c);
      int16_t mapped_red = l_r->at(pre_value.r);
      int16_t mapped_green = l_g->at(pre_value.g);
      int16_t mapped_blue = l_b->at(pre_value.b);
      
      RgbPixel pixel = *new RgbPixel(mapped_red, mapped_green, mapped_blue);
      row_data->push_back(pixel);
    }
    
    result->push_back(row_data);
  }
}

void Picture::histogram_match_gray(Histogram *ref) {
  std::vector<int16_t> *luteq = new std::vector<int16_t>();
  int prev_minima = 0;
  
  for (int i = 0; i < 256; i++) {
    int j = 0;
    uint32_t cdf_data = cdf_gray->data->at(i);

    for (j = prev_minima; j < 256; j++) {
      uint32_t ref_data = ref->data->at(j);
      if (ref_data > cdf_data) {
        prev_minima = j;
        break;
      }
    }
    
    if (HEAVY_DEBUG) {
      printf("%.3d: %.7d | %.7d < %d\n", i, cdf_gray->data->at(i), ref->data->at(i), (uint32_t) prev_minima);
    }
    
    luteq->push_back(prev_minima);
  }
  
  remap_histogram_gray(luteq);
}

void Picture::histogram_match_rgb(Histogram *rr, Histogram *rg, Histogram *rb) {
  std::vector<int16_t> *luteq_r = new std::vector<int16_t>();
  std::vector<int16_t> *luteq_g = new std::vector<int16_t>();
  std::vector<int16_t> *luteq_b = new std::vector<int16_t>();
  
  int prev_minima;
  
  prev_minima = 0;
  for (int i = 0; i < 256; i++) {
    int j = 0;
    uint32_t cdf_data = cdf_r->data->at(i);
    
    for (j = prev_minima; j < 256; j++) {
      uint32_t ref_data = rr->data->at(j);
      if (ref_data > cdf_data) {
        prev_minima = j;
        break;
      }
    }
    
    luteq_r->push_back(prev_minima);
  }
  
  prev_minima = 0;
  for (int i = 0; i < 256; i++) {
    int j = 0;
    uint32_t cdf_data = cdf_g->data->at(i);
    
    for (j = prev_minima; j < 256; j++) {
      uint32_t ref_data = rg->data->at(j);
      if (ref_data > cdf_data) {
        prev_minima = j;
        break;
      }
    }
    
    luteq_g->push_back(prev_minima);
  }
  
  prev_minima = 0;
  for (int i = 0; i < 256; i++) {
    int j = 0;
    uint32_t cdf_data = cdf_b->data->at(i);
    
    for (j = prev_minima; j < 256; j++) {
      uint32_t ref_data = rb->data->at(j);
      if (ref_data > cdf_data) {
        prev_minima = j;
        break;
      }
    }
    
    luteq_b->push_back(prev_minima);
  }
  
  remap_histogram_rgb(luteq_r, luteq_g, luteq_b);
}

void Picture::diamond_warp() {
  float mid_row = dim_y / 2;
  int limit_low = 0;
  int limit_high = dim_y - 1;
  
  initialize_result(0);
  for (int r = 0; r < dim_y; r++) {
    if (r < mid_row) {
      for (int x_prime = 0; x_prime < dim_x; x_prime++) {
        float x = ((float) x_prime - (mid_row - ((float) r + 1))) / (((float) r + 1) / mid_row);
        RgbPixel p = RgbPixel(0, 0, 0);
        if (limit_low <= x && x <= limit_high) {
          p = bilinear_interpolate(x, r);
          //printf("(%d, %.0f) -> (%d, %d)\n", r, x, r, x_prime);
          result->at(r)->at(x_prime) = p;
        }
      }
    } else {
      for (int x_prime = 0; x_prime < dim_x; x_prime++) {
        float x = ((float) x_prime - ((float) r - mid_row)) / (((float) dim_y - (float) r) / mid_row);
        RgbPixel p = RgbPixel(0, 0, 0);
        if (limit_low <= x && x <= limit_high) {
          p = bilinear_interpolate(x, r);
          result->at(r)->at(x_prime) = p;
        }
      }
    }
  }
}

void Picture::find_piece(string piece_one, string piece_two) {
  int c1r, c1c, c2r, c2c, c3r, c3c, c4r, c4c;
  int x1r, x1c, x2r, x2c, x3r, x3c, x4r, x4c;

  int state = SCAN_OUTSIDE_IMAGE;
  bool top_left_started = false;
  bool top_right_started = false;
  bool bottom_left_started = false;
  bool bottom_right_started = false;
  for (int row = 1; row < dim_y - 1; row++) {
    bool is_blank_line = true;
    
    for (int col = 1; col < dim_x - 1; col++) {
      RgbPixel a0 = data->at(row-1)->at(col-1);
      RgbPixel a1 = data->at(row-1)->at(col);
      RgbPixel a2 = data->at(row-1)->at(col+1);
      RgbPixel a3 = data->at(row)->at(col-1);
      RgbPixel a4 = data->at(row)->at(col);
      RgbPixel a5 = data->at(row)->at(col+1);
      RgbPixel a6 = data->at(row+1)->at(col-1);
      RgbPixel a7 = data->at(row+1)->at(col);
      RgbPixel a8 = data->at(row+1)->at(col+1);
      
      
      if (!a8.is_white() &&
          a0.is_white() && a1.is_white() && a2.is_white() && a3.is_white() &&
          a4.is_white() && a5.is_white() && a6.is_white() && a7.is_white()) {
        // Find top-left corner
        state = SCAN_INSIDE_IMAGE;

        if (!top_left_started) {
          top_left_started = true;
          c1r = row + 1;
          c1c = col + 1;
        }
        x1r = row + 1;
        x1c = col + 1;
        //cout << "Top left corner found at " << row + 1 << ", " << col + 1 << endl;
      } else if (!a2.is_white() &&
                 a0.is_white() && a1.is_white() && a3.is_white() && a4.is_white() &&
                 a5.is_white() && a6.is_white() && a7.is_white() && a8.is_white()) {
        // bottom-left corner
        if (!bottom_left_started) {
          bottom_left_started = true;
          c3r = row - 1;
          c3c = col + 1;
        }
        x3r = row - 1;
        x3c = col + 1;
        //cout << "Bottom left corner found at " << row - 1 << ", " << col + 1 << endl;
      } else if (!a6.is_white() &&
                 a0.is_white() && a1.is_white() && a2.is_white() && a3.is_white() &&
                 a4.is_white() && a5.is_white() && a7.is_white() && a8.is_white()) {

        if (!top_right_started) {
          top_right_started = true;
          c2r = row + 1;
          c2c = col - 1;
        }
        x2r = row + 1;
        x2c = col - 1;
        //cout << "Top right corner found at " << row + 1 << ", " << col - 1 << endl;
      } else if (!a0.is_white() &&
                 a1.is_white() && a2.is_white() && a3.is_white() && a4.is_white() &&
                 a5.is_white() && a6.is_white() && a7.is_white() && a8.is_white()) {
        if (!bottom_right_started) {
          bottom_right_started = true;
          c4r = row - 1;
          c4c = col - 1;
        }
        x4r = row - 1;
        x4c = col - 1;
        //cout << "Bottom right corner found at " << row - 1 << ", " << col - 1 << endl;
      }
      
      if (!a4.is_white() || !a1.is_white() || !a7.is_white()) {
        is_blank_line = false;
      }
    }
    
    if (is_blank_line && state == SCAN_INSIDE_IMAGE) {
      state = SCAN_OUTSIDE_IMAGE;
      cout << "Termination detected ===========================" << endl;
//      cout << "Possible corner pairs: " << endl
//      << c1r << ", " << c1c << " | " << x1r << ", " << x1c << endl
//      << c2r << ", " << c2c << " | " << x2r << ", " << x2c << endl
//      << c3r << ", " << c3c << " | " << x3r << ", " << x3c << endl
//      << c4r << ", " << c4c << " | " << x4r << ", " << x4c << endl;
      
      if (c1r < x2r && c1c < x2c && x1r > x2r) {
        cout << "Type 1 detected" << endl;
        cout << "Top left: " << c1r << ", " << c1c << endl;
        cout << "Top right: " << x2r << ", " << x2c << endl;
        cout << "Bottom left: " << c3r << ", " << c3c << endl;
        cout << "Bottom right: " << x4r << ", " << x4c << endl;
        float coldiff = x2c - c1c;
        float rowdiff = x2r - c1r;
        float length = sqrt(coldiff * coldiff + rowdiff * rowdiff);
        cout << "Length = " << length << endl;
        
        vector<vector<float>> base_matrix = vector<vector<float>>();
        vector<float> row = vector<float>();
        row.push_back(1.4292);
        row.push_back(0.3843);
        row.push_back(56.6157);
        base_matrix.push_back(row);
        row = vector<float>();
        row.push_back(-0.3843);
        row.push_back(1.4292);
        row.push_back(94.5708);
        base_matrix.push_back(row);
        row = vector<float>();
        row.push_back(0);
        row.push_back(0);
        row.push_back(1);
        base_matrix.push_back(row);
        
        Matrix bm = Matrix(base_matrix);
        
        result = new vector<vector<RgbPixel>*>();
        for (int res_row = 0; res_row < 101; res_row++) {
          vector<RgbPixel>* row_result = new vector<RgbPixel>();
          for (int res_col = 0; res_col < 101; res_col++) {
            vector<vector<float>> t_matrix = vector<vector<float>>();
            row = vector<float>();
            row.push_back(res_row + 1);
            t_matrix.push_back(row);
            row = vector<float>();
            row.push_back(res_col + 2);
            t_matrix.push_back(row);
            row = vector<float>();
            row.push_back(1);
            t_matrix.push_back(row);
            
            Matrix tm = Matrix(t_matrix);
            Matrix res = bm.multiply(tm);
            //printf("(%.2f, %.2f) <- (%d, %d)\n", res.data.at(0).at(0), res.data.at(1).at(0), res_row, res_col);
            RgbPixel rp = bilinear_interpolate(res.data.at(1).at(0), res.data.at(0).at(0));
            
            row_result->push_back(rp);
          }
          result->push_back(row_result);
        }
        
        write_rgb(piece_one);
      } else {
        cout << "Type 2 detected" << endl;
        cout << "Top left: " << x1r << ", " << x1c << endl;
        cout << "Top right: " << c2r << ", " << c2c << endl;
        cout << "Bottom left: " << x3r << ", " << x3c << endl;
        cout << "Bottom right: " << c4r << ", " << c4c << endl;
        float coldiff = c2c - x1c;
        float rowdiff = c2r - x1r;
        float length = sqrt(coldiff * coldiff + rowdiff * rowdiff);
        cout << "Length = " << length << endl;
        
        vector<vector<float>> base_matrix = vector<vector<float>>();
        vector<float> row = vector<float>();
        row.push_back(-0.0653);
        row.push_back(-0.7170);
        row.push_back(369.2030);
        base_matrix.push_back(row);
        row = vector<float>();
        row.push_back(0.7170);
        row.push_back(-0.0653);
        row.push_back(307.9390);
        base_matrix.push_back(row);
        row = vector<float>();
        row.push_back(0);
        row.push_back(0);
        row.push_back(1);
        base_matrix.push_back(row);
        
        Matrix bm = Matrix(base_matrix);
        
        result = new vector<vector<RgbPixel>*>();
        for (int res_row = 0; res_row < 101; res_row++) {
          vector<RgbPixel>* row_result = new vector<RgbPixel>();
          for (int res_col = 0; res_col < 101; res_col++) {
            vector<vector<float>> t_matrix = vector<vector<float>>();
            row = vector<float>();
            row.push_back(res_row + 3);
            t_matrix.push_back(row);
            row = vector<float>();
            row.push_back(res_col + 0);
            t_matrix.push_back(row);
            row = vector<float>();
            row.push_back(1);
            t_matrix.push_back(row);
            
            Matrix tm = Matrix(t_matrix);
            Matrix res = bm.multiply(tm);
            //printf("(%.2f, %.2f) <- (%d, %d)\n", res.data.at(0).at(0), res.data.at(1).at(0), res_row, res_col);
            RgbPixel rp = bilinear_interpolate(res.data.at(1).at(0), res.data.at(0).at(0));
            
            row_result->push_back(rp);
          }
          result->push_back(row_result);
        }
        
        write_rgb(piece_two);
      }

      top_left_started = false;
      top_right_started = false;
      bottom_left_started = false;
      bottom_right_started = false;
//      cout << "Corners: " << endl
//      << c1r << ", " << c1c << endl
//      << c2r << ", " << c2c << endl
//      << c3r << ", " << c3c << endl
//      << c4r << ", " << c4c << endl;

    }
    
    // cout << "----\n" << endl;
  }
}

void Picture::find_hole(int *trcr, int *trcc, int *brcr, int *brcc) {
  for (int row = 1; row < dim_y - 1; row++) {
    for (int col = 1; col < dim_x - 1; col++) {
      RgbPixel a0 = data->at(row-1)->at(col-1);
      RgbPixel a1 = data->at(row-1)->at(col);
      RgbPixel a2 = data->at(row-1)->at(col+1);
      RgbPixel a3 = data->at(row)->at(col-1);
      RgbPixel a4 = data->at(row)->at(col);
      RgbPixel a5 = data->at(row)->at(col+1);
      RgbPixel a6 = data->at(row+1)->at(col-1);
      RgbPixel a7 = data->at(row+1)->at(col);
      RgbPixel a8 = data->at(row+1)->at(col+1);
      
      if (!a0.is_white() && !a1.is_white() && !a2.is_white() && !a3.is_white() && !a6.is_white()
          && a4.is_white() && a5.is_white() && a7.is_white() && a8.is_white()) {
        printf("left corner at %d, %d\n", row, col);
        *trcr = row;
        *trcc = col;
      } else if (a0.is_white() && a1.is_white() && a3.is_white() && a4.is_white()
                 && !a2.is_white() && !a5.is_white() && !a6.is_white() && !a7.is_white() && !a8.is_white()) {
        printf("right corner at %d, %d\n", row, col);
        *brcr = row;
        *brcc = col;
      }
    }
  }
}

void Picture::fit_piece(Picture piece, int tlcr, int tlcc, int brcr, int brcc) {
  result = data;
  
  for (int r = tlcr; r <= brcr; r++) {
    for (int c = tlcc; c <= brcc; c++) {
      result->at(r)->at(c) = piece.data->at(r - tlcr)->at(c - tlcc);
    }
  }
}

void Picture::overlay_with(Picture other) {
  copy_data_to_result();
  
  vector<float> tfm = { -1.1210,
                        -0.8904,
                       980.7080,
                         1.1998,
                        -0.0941,
                      -657.0232,
                        -0.0033,
                        -0.0001,
                         1.0};
  Matrix mat = Matrix(tfm, 3);
  int limit_row_low = 0;
  int limit_col_low = 0;
  int limit_row_high = other.dim_y - 1;
  int limit_col_high = other.dim_x - 1;
  
  for (int r = 0; r < dim_y; r++) {
    for (int c = 0; c < dim_x; c++) {
      vector<float> _pos = { (float) r, (float) c, (float) 1 };
      Matrix pos = Matrix(_pos, 1);
      
      Matrix res = mat.multiply(pos);
      float row = res.data.at(0).at(0) / res.data.at(2).at(0);
      float col = res.data.at(1).at(0) / res.data.at(2).at(0);
      
      if (limit_row_low <= row && row < limit_row_high &&
          limit_col_low <= col && col < limit_col_high) {
        RgbPixel p = other.bilinear_interpolate(col, row);
        result->at(r)->at(c) = p;
      }
    }
  }
}

void Picture::dither(int method) {
  vector<int> levels = {};
  switch(method) {
    case DITHER_2: dither_2(levels); break;
    case DITHER_4: dither_4(levels); break;
    case DITHER_4A: dither_4a(levels); break;
    case DITHER_8: dither_8(levels); break;
    case DITHER_FSB: dither_fsb(); break;
    case DITHER_JJN: dither_jjn(); break;
    case DITHER_STUCKI: dither_stucki(); break;
  }
}

void Picture::dither_fsb() {
  vector<vector<float>> quanterror = vector<vector<float>>();
  result_gray = new vector<vector<uint8_t>>();
  
  // Reserve spaces for dim_x * dim_y error structure;
  for (int prefill = 0; prefill < dim_y; prefill++) {
    vector<uint8_t> row_gray = vector<uint8_t>(dim_x);
    vector<float> row_error = vector<float>(dim_x, 0);
    
    result_gray->push_back(row_gray);
    quanterror.push_back(row_error);
  }
  
  
  for (int r = 0; r < dim_y; r += 2) {
    for (int c = 0; c < dim_x; c++) {
      float quanterror_here = quanterror.at(r).at(c);
      int current_pixel = (int) data_gray->at(r).at(c);
      int updated_pixel = (current_pixel + quanterror_here) > 127 ? 255 : 0;
      int error = current_pixel - updated_pixel;
      
      result_gray->at(r).at(c) = updated_pixel;
      
      //printf("%.2f + %d => %d (%d)\n", quanterror_here, current_pixel, updated_pixel, error);
      if (c < dim_x - 1) {
        quanterror.at(r).at(c+1) += (float) 7 / (float) 16 * (float) error;
        //cout << "    " << quanterror.at(r).at(c+1) << endl;
      }
      
      if (r < dim_y - 1) {
        quanterror.at(r+1).at(c) += (float) 5 / (float) 16 * (float) error;
        //cout << "    " << quanterror.at(r+1).at(c) << endl;
        
        if (c < dim_x - 1) {
          quanterror.at(r+1).at(c+1) += (float) 1 / (float) 16 * (float) error;
          //cout << "    " << quanterror.at(r+1).at(c+1) << endl;
        }
        
        if (c > 0) {
          quanterror.at(r+1).at(c-1) += (float) 3 / (float) 16 * (float) error;
          //cout << "    " << quanterror.at(r+1).at(c-1) << endl;
        }
      }
    }
    
    for (int c = dim_x - 1; c >= 0; c--) {
      float quanterror_here = quanterror.at(r+1).at(c);
      int current_pixel = (int) data_gray->at(r+1).at(c);
      int updated_pixel = (current_pixel + quanterror_here) > 127 ? 255 : 0;
      int error = current_pixel - updated_pixel;
      
      result_gray->at(r+1).at(c) = updated_pixel;
      
      //printf("%.2f + %d => %d (%d)\n", quanterror_here, current_pixel, updated_pixel, error);
      if (c > 0) {
        quanterror.at(r+1).at(c-1) += (float) 7 / (float) 16 * (float) error;
        //cout << "    " << quanterror.at(r).at(c+1) << endl;
      }
      
      if (r < dim_y - 2) {
        quanterror.at(r+2).at(c) += (float) 5 / (float) 16 * (float) error;
        //cout << "    " << quanterror.at(r+1).at(c) << endl;
        
        if (c > 0) {
          quanterror.at(r+2).at(c-1) += (float) 1 / (float) 16 * (float) error;
          //cout << "    " << quanterror.at(r+1).at(c+1) << endl;
        }
        
        if (c < dim_x - 1) {
          quanterror.at(r+2).at(c+1) += (float) 3 / (float) 16 * (float) error;
          //cout << "    " << quanterror.at(r+1).at(c-1) << endl;
        }
      }
    }
  }
}

void Picture::dither_jjn() {
  vector<vector<float>> quanterror = vector<vector<float>>();
  result_gray = new vector<vector<uint8_t>>();
  
  // Reserve spaces for dim_x * dim_y error structure;
  for (int prefill = 0; prefill < dim_y; prefill++) {
    vector<uint8_t> row_gray = vector<uint8_t>(dim_x);
    vector<float> row_error = vector<float>(dim_x, 0);
    
    result_gray->push_back(row_gray);
    quanterror.push_back(row_error);
  }
  
  
  for (int r = 0; r < dim_y; r += 2) {
    for (int c = 0; c < dim_x; c++) {
      float quanterror_here = quanterror.at(r).at(c);
      int current_pixel = (int) data_gray->at(r).at(c);
      int updated_pixel = (current_pixel + quanterror_here) > 127 ? 255 : 0;
      int error = current_pixel - updated_pixel;
      
      result_gray->at(r).at(c) = updated_pixel;
      
      if (c < dim_x - 1) {
        quanterror.at(r).at(c+1) += (float) 7 / (float) 48 * (float) error;
      }
      
      if (c < dim_x - 2) {
        quanterror.at(r).at(c+2) += (float) 5 / (float) 48 * (float) error;
      }
      
      if (r < dim_y - 1) {
        if (c > 1) {
          quanterror.at(r+1).at(c-2) += (float) 3 / (float) 48 * (float) error;
        }
        
        if (c > 0) {
          quanterror.at(r+1).at(c-1) += (float) 5 / (float) 48 * (float) error;
        }
        
        quanterror.at(r+1).at(c) += (float) 7 / (float) 48 * (float) error;
        
        if (c < dim_x - 1) {
          quanterror.at(r+1).at(c+1) += (float) 5 / (float) 48 * (float) error;
        }
        
        if (c < dim_x - 2) {
          quanterror.at(r+1).at(c+2) += (float) 3 / (float) 48 * (float) error;
        }
      }
      
      if (r < dim_y - 2) {
        if (c > 1) {
          quanterror.at(r+2).at(c-2) += (float) 1 / (float) 48 * (float) error;
        }
        
        if (c > 0) {
          quanterror.at(r+2).at(c-1) += (float) 3 / (float) 48 * (float) error;
        }
        
        quanterror.at(r+2).at(c) += (float) 5 / (float) 48 * (float) error;
        
        if (c < dim_x - 1) {
          quanterror.at(r+2).at(c+1) += (float) 3 / (float) 48 * (float) error;
        }
        
        if (c < dim_x - 2) {
          quanterror.at(r+2).at(c+2) += (float) 1 / (float) 48 * (float) error;
        }
      }
    }
    
    for (int c = dim_x - 1; c >= 0; c--) {
      float quanterror_here = quanterror.at(r+1).at(c);
      int current_pixel = (int) data_gray->at(r+1).at(c);
      int updated_pixel = (current_pixel + quanterror_here) > 127 ? 255 : 0;
      int error = current_pixel - updated_pixel;
      
      result_gray->at(r+1).at(c) = updated_pixel;
      
      if (c > 1) {
        quanterror.at(r).at(c-2) += (float) 5 / (float) 48 * (float) error;
      }
      
      if (c > 0) {
        quanterror.at(r).at(c-1) += (float) 7 / (float) 48 * (float) error;
      }
      
      
      if (r < dim_y - 2) {
        if (c > 1) {
          quanterror.at(r+2).at(c-2) += (float) 3 / (float) 48 * (float) error;
        }
        
        if (c > 0) {
          quanterror.at(r+2).at(c-1) += (float) 5 / (float) 48 * (float) error;
        }
        
        quanterror.at(r+2).at(c) += (float) 7 / (float) 48 * (float) error;
        
        if (c < dim_x - 1) {
          quanterror.at(r+2).at(c+1) += (float) 5 / (float) 48 * (float) error;
        }
        
        if (c < dim_x - 2) {
          quanterror.at(r+2).at(c+2) += (float) 3 / (float) 48 * (float) error;
        }
      }
      
      if (r < dim_y - 3) {
        if (c > 1) {
          quanterror.at(r+3).at(c-2) += (float) 1 / (float) 48 * (float) error;
        }
        
        if (c > 0) {
          quanterror.at(r+3).at(c-1) += (float) 3 / (float) 48 * (float) error;
        }
        
        quanterror.at(r+3).at(c) += (float) 5 / (float) 48 * (float) error;
        
        if (c < dim_x - 1) {
          quanterror.at(r+3).at(c+1) += (float) 3 / (float) 48 * (float) error;
        }
        
        if (c < dim_x - 2) {
          quanterror.at(r+3).at(c+2) += (float) 1 / (float) 48 * (float) error;
        }
      }
    }
  }
}

void Picture::dither_stucki() {
  vector<vector<float>> quanterror = vector<vector<float>>();
  result_gray = new vector<vector<uint8_t>>();
  
  // Reserve spaces for dim_x * dim_y error structure;
  for (int prefill = 0; prefill < dim_y; prefill++) {
    vector<uint8_t> row_gray = vector<uint8_t>(dim_x);
    vector<float> row_error = vector<float>(dim_x, 0);
    
    result_gray->push_back(row_gray);
    quanterror.push_back(row_error);
  }
  
  
  for (int r = 0; r < dim_y; r += 2) {
    for (int c = 0; c < dim_x; c++) {
      float quanterror_here = quanterror.at(r).at(c);
      int current_pixel = (int) data_gray->at(r).at(c);
      int updated_pixel = (current_pixel + quanterror_here) > 127 ? 255 : 0;
      int error = current_pixel - updated_pixel;
      
      result_gray->at(r).at(c) = updated_pixel;
      
      if (c < dim_x - 1) {
        quanterror.at(r).at(c+1) += (float) 8 / (float) 42 * (float) error;
      }
      
      if (c < dim_x - 2) {
        quanterror.at(r).at(c+2) += (float) 4 / (float) 42 * (float) error;
      }
      
      if (r < dim_y - 1) {
        if (c > 1) {
          quanterror.at(r+1).at(c-2) += (float) 2 / (float) 42 * (float) error;
        }
        
        if (c > 0) {
          quanterror.at(r+1).at(c-1) += (float) 4 / (float) 42 * (float) error;
        }
        
        quanterror.at(r+1).at(c) += (float) 8 / (float) 42 * (float) error;
        
        if (c < dim_x - 1) {
          quanterror.at(r+1).at(c+1) += (float) 4 / (float) 42 * (float) error;
        }
        
        if (c < dim_x - 2) {
          quanterror.at(r+1).at(c+2) += (float) 2 / (float) 42 * (float) error;
        }
      }
      
      if (r < dim_y - 2) {
        if (c > 1) {
          quanterror.at(r+2).at(c-2) += (float) 1 / (float) 42 * (float) error;
        }
        
        if (c > 0) {
          quanterror.at(r+2).at(c-1) += (float) 2 / (float) 42 * (float) error;
        }
        
        quanterror.at(r+2).at(c) += (float) 4 / (float) 42 * (float) error;
        
        if (c < dim_x - 1) {
          quanterror.at(r+2).at(c+1) += (float) 2 / (float) 42 * (float) error;
        }
        
        if (c < dim_x - 2) {
          quanterror.at(r+2).at(c+2) += (float) 1 / (float) 42 * (float) error;
        }
      }
    }
    
    for (int c = dim_x - 1; c >= 0; c--) {
      float quanterror_here = quanterror.at(r+1).at(c);
      int current_pixel = (int) data_gray->at(r+1).at(c);
      int updated_pixel = (current_pixel + quanterror_here) > 127 ? 255 : 0;
      int error = current_pixel - updated_pixel;
      
      result_gray->at(r+1).at(c) = updated_pixel;
      
      if (c > 1) {
        quanterror.at(r).at(c-2) += (float) 5 / (float) 48 * (float) error;
      }
      
      if (c > 0) {
        quanterror.at(r).at(c-1) += (float) 7 / (float) 48 * (float) error;
      }
      
      
      if (r < dim_y - 2) {
        if (c > 1) {
          quanterror.at(r+2).at(c-2) += (float) 3 / (float) 48 * (float) error;
        }
        
        if (c > 0) {
          quanterror.at(r+2).at(c-1) += (float) 5 / (float) 48 * (float) error;
        }
        
        quanterror.at(r+2).at(c) += (float) 7 / (float) 48 * (float) error;
        
        if (c < dim_x - 1) {
          quanterror.at(r+2).at(c+1) += (float) 5 / (float) 48 * (float) error;
        }
        
        if (c < dim_x - 2) {
          quanterror.at(r+2).at(c+2) += (float) 3 / (float) 48 * (float) error;
        }
      }
      
      if (r < dim_y - 3) {
        if (c > 1) {
          quanterror.at(r+3).at(c-2) += (float) 1 / (float) 48 * (float) error;
        }
        
        if (c > 0) {
          quanterror.at(r+3).at(c-1) += (float) 3 / (float) 48 * (float) error;
        }
        
        quanterror.at(r+3).at(c) += (float) 5 / (float) 48 * (float) error;
        
        if (c < dim_x - 1) {
          quanterror.at(r+3).at(c+1) += (float) 3 / (float) 48 * (float) error;
        }
        
        if (c < dim_x - 2) {
          quanterror.at(r+3).at(c+2) += (float) 1 / (float) 48 * (float) error;
        }
      }
    }
  }
}

void Picture::dither_multi_level(int method) {
  vector<int> levels = { 0, 85, 170, 255 };
  switch(method) {
    case DITHER_2: dither_2(levels); break;
    case DITHER_4: dither_4(levels); break;
    case DITHER_4A: dither_4a(levels); break;
    case DITHER_8: dither_8(levels); break;
  }
}

void Picture::apply_dithering(Matrix dither, vector<int> levels) {
  result_gray = new vector<vector<uint8_t>>();
  int modulus = dither.data.size();
  bool use_multi_level = true;
  
  if (levels.size() == 0) {
    use_multi_level = false;
  }
  
  for (int r = 0; r < dim_y; r++) {
    vector<uint8_t> row_gray = vector<uint8_t>();
    for (int c = 0; c < dim_x; c++) {
      int pixel = data_gray->at(r).at(c);
      float bayer = dither.data.at(r % modulus).at(c % modulus);
      
      if (use_multi_level) {
        int fcp = find_closest_palette((float) pixel/bayer * 127, levels);
        //printf("%d | %.3f -> %d\n", pixel, bayer, fcp);

        
        row_gray.push_back(fcp);
      } else {
        row_gray.push_back(pixel > bayer ? 255 : 0);
      }
    }
    
    result_gray->push_back(row_gray);
  }
}

void Picture::dither_8(vector<int> levels) {
  vector<vector<float>> mat = vector<vector<float>>();
  vector<float> d = { 0, 32, 8, 40, 2, 34, 10, 42 };
  mat.push_back(d);
  d = { 48, 16, 56, 24, 50, 18, 58, 26 };
  mat.push_back(d);
  d = { 12, 44,  4, 36, 14, 46,  6, 38 };
  mat.push_back(d);
  d = { 60, 28, 52, 20, 62, 30, 54, 22 };
  mat.push_back(d);
  d = {  3, 35, 11, 43,  1, 33,  9, 41 };
  mat.push_back(d);
  d = { 51, 19, 59, 27, 49, 17, 57, 25 };
  mat.push_back(d);
  d = { 15, 47,  7, 39, 13, 45,  5, 37 };
  mat.push_back(d);
  d = { 63, 31, 55, 23, 61, 29, 53, 21 };
  mat.push_back(d);
  
  Matrix m = Matrix(mat);
  m.thresholdize();
  
  apply_dithering(m, levels);
  
//  for (int r = 0; r < dim_y; r++) {
//    vector<uint8_t> row_gray = vector<uint8_t>();
//    for (int c = 0; c < dim_x; c++) {
//      int pixel = data_gray->at(r).at(c);
//      float bayer = m.data.at(r % 8).at(c % 8);
//      
//      row_gray.push_back(pixel > bayer ? 255 : 0);
//    }
//    result_gray->push_back(row_gray);
//  }
}

void Picture::dither_4(vector<int> levels) {
  vector<vector<float>> mat = vector<vector<float>>();
  vector<float> d = { 0, 8, 2, 10 };
  mat.push_back(d);
  d = { 12,  4, 14,  6 };
  mat.push_back(d);
  d = {  3, 11,  1,  9 };
  mat.push_back(d);
  d = { 15,  7, 13,  5 };
  mat.push_back(d);
  
  Matrix m = Matrix(mat);
  m.thresholdize();
  
  apply_dithering(m, levels);
}

void Picture::dither_4a(vector<int> levels) {
  vector<vector<float>> mat = vector<vector<float>>();
  vector<float> d = { 14, 10, 11, 15 };
  mat.push_back(d);
  d = {  9,  3,  0,  4 };
  mat.push_back(d);
  d = {  8,  2,  1,  5 };
  mat.push_back(d);
  d = { 13,  7,  6, 12 };
  mat.push_back(d);
  
  Matrix m = Matrix(mat);
  m.thresholdize();
  
  apply_dithering(m, levels);
}

void Picture::dither_2(vector<int> levels) {
  vector<vector<float>> mat = vector<vector<float>>();
  vector<float> d = vector<float>();
  d.push_back(0.5 / 4 * 255);
  d.push_back(2.5 / 4 * 255);
  mat.push_back(d);
  d = vector<float>();
  d.push_back(3.5 / 4 * 255);
  d.push_back(1.5 / 4 * 255);
  mat.push_back(d);
  Matrix m = Matrix(mat);
  
  apply_dithering(m, levels);
  
//  result_gray = new vector<vector<uint8_t>>();
//  
//  for (int r = 0; r < dim_y; r += 2) {
//    vector<uint8_t> row_gray_0 = vector<uint8_t>();
//    vector<uint8_t> row_gray_1 = vector<uint8_t>();
//    
//    for (int c = 0; c < dim_x; c += 2) {
//      uint8_t p0 = data_gray->at(r).at(c);
//      uint8_t p1 = data_gray->at(r).at(c+1);
//      uint8_t p2 = data_gray->at(r+1).at(c);
//      uint8_t p3 = data_gray->at(r+1).at(c+1);
//      
//      p0 = p0 > m.data.at(0).at(0) ? 255 : 0;
//      p1 = p1 > m.data.at(0).at(1) ? 255 : 0;
//      p2 = p2 > m.data.at(1).at(0) ? 255 : 0;
//      p3 = p3 > m.data.at(1).at(1) ? 255 : 0;
//      
//      row_gray_0.push_back(p0);
//      row_gray_0.push_back(p1);
//      row_gray_1.push_back(p2);
//      row_gray_1.push_back(p3);
//    }
//    
//    result_gray->push_back(row_gray_0);
//    result_gray->push_back(row_gray_1);
//  }
  
//  for (int r = 0; r < dim_y; r++) {
//    for (int c = 0; c < dim_x; c++) {
//      vector<vector<float>> img = vector<vector<float>>();
//      vector<float> i = vector<float>();
//      uint8_t a0 = data_gray->at(abs(r - 1)).at(abs(c - 1));
//      uint8_t a1 = data_gray->at(abs(r - 1)).at(abs(c));
//      uint8_t a2 = data_gray->at(abs(r)).at(abs(c - 1));
//      uint8_t a3 = data_gray->at(abs(r)).at(abs(c));
//      
//      i.push_back(a0);
//      i.push_back(a1);
//      img.push_back(i);
//      i = vector<float>();
//      i.push_back(a2);
//      i.push_back(a3);
//      img.push_back(i);
//      Matrix mimg = Matrix(img);
//      float mres = m.multiply_and_average (mimg);
//      printf("(%d, %d): %.2f\n", r, c, mres);
//
//    }
//  }
}

int Picture::find_closest_palette(float val, std::vector<int> palettes) {
  float minima = __FLT_MAX__;
  int index = -1;
  
  if (val < 85) {
    return 0;
  } else if (val > 170) {
    return 255;
  }
  
  for (int i = 0; i < palettes.size(); i++) {
    float diff = abs(val - palettes.at(i));
    if (diff < minima) {
      minima = diff;
      index = i;
    }
  }
  
  return palettes.at(index);
}

void Picture::to_grayscale() {
  result_gray = new vector<vector<uint8_t>>();
  type = COLOR_GRAY;
  
  for (auto r = 0; r < dim_y; r++) {
    vector<uint8_t> row_gray = vector<uint8_t>();
    for (auto c = 0; c < dim_x; c++) {
      RgbPixel p = data->at(r)->at(c);
      // Using luminosity method
      float psv = 0.9 * (float) p.r + 0.1 * (float) p.g + 0.00 * (float) p.b;
      row_gray.push_back(psv);
    }
    
    result_gray->push_back(row_gray);
  }
}

void Picture::adaptive_thresholding() {
  vector<uint32_t> h_data = *hist_gray->data;
  int minima = 255;
  int maxima = 0;
  float m_threshold = 0.005 * (float) dim_x * (float) dim_y;
  for (int i = 0; i < h_data.size(); i++) {
    if (h_data.at(i) > m_threshold) {
      if (i < minima) {
        minima = i;
      }
      
      if (i > maxima) {
        maxima = i;
      }
    }
  }
  
  cout << "Min/max " << minima << " -> " << maxima << endl;
  result_gray = new vector<vector<uint8_t>>();
  
  for (int r = 0; r < dim_y; r++) {
    vector<uint8_t> row_gray = vector<uint8_t>();
    for (int c = 0; c < dim_x; c++) {
      if (data_gray->at(r).at(c) > minima && data_gray->at(r).at(c) < maxima) {
        row_gray.push_back(0);
      } else {
        row_gray.push_back(255);
      }
    }
    
    result_gray->push_back(row_gray);
  }
}

void Picture::morph_erode() {
  result_gray = new vector<vector<uint8_t>>();
  
  for (int r = 0; r < dim_y; r++) {
    vector<uint8_t> row_gray = vector<uint8_t>();
    for (int c = 0; c < dim_x; c++) {
      row_gray.push_back(data_gray->at(r).at(c));
    }
    result_gray->push_back(row_gray);
  }
  
  vector<vector<float>> m = vector<vector<float>>();
  vector<float> m_r = { 1, 1, 1 };
  m.push_back(m_r);
  m.push_back(m_r);
  m.push_back(m_r);
  
  Matrix mat = Matrix(m);
  
  for (int r = 1; r < dim_y - 1; r++) {
    for (int c = 1; c < dim_x - 1; c++) {
      vector<vector<float>> _image = vector<vector<float>>();
      vector<float> _image_r = vector<float>();
      _image_r.push_back(data_gray->at(r-1).at(c-1));
      _image_r.push_back(data_gray->at(r-1).at(c));
      _image_r.push_back(data_gray->at(r-1).at(c+1));
      _image.push_back(_image_r);
      _image_r = vector<float>();
      _image_r.push_back(data_gray->at(r).at(c-1));
      _image_r.push_back(data_gray->at(r).at(c));
      _image_r.push_back(data_gray->at(r).at(c+1));
      _image.push_back(_image_r);
      _image_r = vector<float>();
      _image_r.push_back(data_gray->at(r+1).at(c-1));
      _image_r.push_back(data_gray->at(r+1).at(c));
      _image_r.push_back(data_gray->at(r+1).at(c+1));
      _image.push_back(_image_r);
      Matrix image = Matrix(_image);
      
      
      int erosion = mat.erode(image);
      result_gray->at(r).at(c) = erosion;
    }
  }
}

void Picture::post_process_threshold() {
  int radius = 3;
  result_gray = data_gray;
  
  for (int r = radius; r < dim_y - radius; r++) {
    for (int c = radius; c < dim_x - radius; c++) {
      int h_count = 0;
      int l_count = 0;
      for (int ir = r - radius; ir <= r + radius; ir++) {
        for (int ic = c - radius; ic <= c + radius; ic++) {
          if (data_gray->at(ir).at(ic) == 0) {
            l_count++;
          } else {
            h_count++;
          }
        }
      }
      
      if (h_count >= l_count) {
        result_gray->at(r).at(c) = 255;
      } else {
        result_gray->at(r).at(c) = 0;
      }
    }
  }
}

GrainCategorizer Picture::count_objects() {
  initialize_result(0);

  vector<bool> _diag_enter        = { 0, 0, 1, 0, 1, 1, 1, 1, 1 };
  vector<bool> _straight_enter    = { 0, 1, 1, 0, 1, 1, 0, 1, 1 };
  vector<bool> _rdiag_enter       = { 1, 1, 1, 0, 1, 1, 0, 0, 1 };
  vector<bool> _triag_enter       = { 0, 0, 1, 0, 1, 1, 0, 0, 1 };
  vector<bool> _utri_enter        = { 0, 1, 1, 0, 1, 1, 0, 0, 1 };
  vector<bool> _ltri_enter        = { 0, 0, 1, 0, 1, 1, 0, 1, 1 };
  vector<bool> _dp_enter          = { 0, 0, 0, 0, 1, 1, 1, 1, 1 };
  vector<bool> _dt_enter          = { 0, 0, 0, 0, 1, 0, 1, 1, 1 };
  vector<bool> _lp_enter          = { 1, 1, 1, 0, 1, 1, 0, 0, 0 };
  vector<bool> _lt_enter          = { 1, 1, 1, 0, 1, 0, 0, 0, 0 };
  vector<bool> _weak_down         = { 0, 0, 0, 0, 0, 0, 0, 1, 1 };
  vector<bool> _weak_se           = { 0, 0, 0, 0, 0, 1, 0, 1, 1 };
  vector<bool> _diag_exit         = { 1, 1, 1, 1, 1, 0, 1, 0, 0 };
  vector<bool> _straight_exit     = { 1, 1, 0, 1, 1, 0, 1, 1, 0 };
  vector<bool> _rdiag_exit        = { 1, 0, 0, 1, 1, 0, 1, 1, 1 };
  BinaryMatrix diag_enter = BinaryMatrix(_diag_enter, 3);
  BinaryMatrix straight_enter = BinaryMatrix(_straight_enter, 3);
  BinaryMatrix rdiag_enter = BinaryMatrix(_rdiag_enter, 3);
  BinaryMatrix triag_enter = BinaryMatrix(_triag_enter, 3);
  BinaryMatrix utri_enter = BinaryMatrix(_utri_enter, 3);
  BinaryMatrix ltri_enter = BinaryMatrix(_ltri_enter, 3);
  BinaryMatrix dp_enter = BinaryMatrix(_dp_enter, 3);
  BinaryMatrix dt_enter = BinaryMatrix(_dt_enter, 3);
  BinaryMatrix lp_enter = BinaryMatrix(_lp_enter, 3);
  BinaryMatrix lt_enter = BinaryMatrix(_lt_enter, 3);
  BinaryMatrix weak_down = BinaryMatrix(_weak_down, 3);
  BinaryMatrix weak_se = BinaryMatrix(_weak_se, 3);
  BinaryMatrix diag_exit = BinaryMatrix(_diag_exit, 3);
  BinaryMatrix straight_exit = BinaryMatrix(_straight_exit, 3);
  BinaryMatrix rdiag_exit = BinaryMatrix(_rdiag_exit, 3);
  GrainCategorizer gc = GrainCategorizer();
  
  for (int r = 1; r < dim_y - 1; r++) {
    for (int c = 1; c < dim_x - 1; c++) {
      Matrix img = extract_matrix(r, c, 1);
      bool diag_enter_match = diag_enter.match(img);
      bool straight_enter_match = straight_enter.match(img);
      bool rdiag_enter_match = rdiag_enter.match(img);
      bool triag_enter_match = triag_enter.match(img);
      bool utri_enter_match = utri_enter.match(img);
      bool ltri_enter_match = ltri_enter.match(img);
      bool dp_enter_match = dp_enter.match(img);
      bool dt_enter_match = dt_enter.match(img);
      bool lp_enter_match = lp_enter.match(img);
      bool lt_enter_match = lt_enter.match(img);
      bool weak_down_match = weak_down.match(img);
      bool weak_se_match = weak_se.match(img);
      
//      bool diag_exit_match = diag_exit.match(img);
//      bool straight_exit_match = straight_exit.match(img);
//      bool rdiag_exit_match = rdiag_exit.match(img);
      
      if (diag_enter_match) {
        //printf("Diag matched at %d, %d\n", r, c);
        gc.add(r, c);
      }
      if (straight_enter_match) {
        //printf("Straight matched at %d, %d\n", r, c);
        gc.add(r, c);
      }
      if (rdiag_enter_match) {
        //printf("Rdiag matched at %d, %d\n", r, c);
        gc.add(r, c);
      }
      if (triag_enter_match) {
        gc.add(r, c);
      }
      if (utri_enter_match) {
        gc.add(r, c);
      }
      if (ltri_enter_match) {
        gc.add(r, c);
      }
      if (dp_enter_match) {
        gc.add(r, c);
      }
      if (dt_enter_match) {
        gc.add(r, c);
      }
      if (lp_enter_match) {
        gc.add(r, c);
      }
      if (lt_enter_match) {
        gc.add(r, c);
      }
      if (weak_down_match) {
        gc.add(r, c);
      }
      if (weak_se_match) {
        gc.add(r, c);
      }
      
      // Ambiguous, don't use
//      if (down_enter_match) {
//        gc.add(r, c);
//      }
//      if (up_enter_match) {
//        gc.add(r, c);
//      }
      
//      if (diag_exit_match) {
//        printf("Diag exit at %d, %d\n", r, c);
//      }
//      if (straight_exit_match) {
//        printf("Straight exit at %d, %d\n", r, c);
//      }
//      if (rdiag_exit_match) {
//        printf("Rdiag exit at %d, %d\n", r, c);
//      }
    }
  }
  
  // gc.debug_groups();
  cout << gc.count_groups() << " grains detected\n";
  
  for (int g = 0; g < gc.grains.size(); g++) {
    if (gc.grains.at(g).size() < GRAIN_BORDER_THRESHOLD) {
      continue;
    }
    
    vector<Coordinate> members = gc.grains.at(g);
    
    int bb_row_low = 0xFFFF;
    int bb_row_high = 0;
    int bb_col_low = 0xFFFF;
    int bb_col_high = 0;
    
    for (int m = 0; m < members.size(); m++) {
      int this_row = members.at(m).row;
      int this_col = members.at(m).col;
      if (this_row > bb_row_high) {
        bb_row_high = this_row;
      }
      if (this_row < bb_row_low) {
        bb_row_low = this_row;
      }
      if (this_col > bb_col_high) {
        bb_col_high = this_col;
      }
      if (this_col < bb_col_low) {
        bb_col_low = this_col;
      }
      
      result_gray->at(this_row).at(this_col) = (g + 23) * 73;
    }
    
//    for (int rr = bb_row_low; rr <= bb_row_high; rr++) {
//      for (int cc = bb_col_low; cc <= bb_col_high; cc++) {
//        result_gray->at(rr).at(cc) = 255;
//      }
//    }
  }
  
  return gc;
}

bool Picture::set_compare(vector<Coordinate> c, Coordinate in) {
  for (int i = 0; i < c.size(); i++) {
    Coordinate existing = c.at(i);
    
    if (existing.row == in.row && existing.col == in.col) {
      return false;
    }
  }
  
  return true;
}

vector<vector<Coordinate>> Picture::compute_spatial_data(GrainCategorizer gc) {
  vector<vector<Coordinate>> spatial_data = vector<vector<Coordinate>>();
  
  for (int g = 0; g < gc.grains.size(); g++) {
    if (gc.grains.at(g).size() < GRAIN_BORDER_THRESHOLD) {
      continue;
    }
    
    vector<Coordinate> spatial_coords = vector<Coordinate>();
    
    
    // expand left first;
    for (int h = 0; h < gc.grains.at(g).size(); h++) {
      Coordinate this_coord = gc.grains.at(g).at(h);
      
      bool still_inside = true;
      int subtractor = 1;
      
      spatial_coords.push_back(gc.grains.at(g).at(h));
      
      while (still_inside) {
        Matrix s_left = extract_matrix(this_coord.row, this_coord.col - subtractor, 3);
        still_inside = s_left.exceed_threshold(0.6);
        if (set_compare(spatial_coords, Coordinate(this_coord.row, this_coord.col - subtractor))) {
          spatial_coords.push_back(Coordinate(this_coord.row, this_coord.col - subtractor));
        }
        subtractor++;
      }
      
      //printf("  Enter (%d, %d)\n", this_coord.row, this_coord.col);
      //cout << "Leaving left-boundary at " << this_coord.row << ", " << this_coord.col - (subtractor - 1) << endl;
    }
    
    // then expand right;
    for (int h = 0; h < gc.grains.at(g).size(); h++) {
      Coordinate this_coord = gc.grains.at(g).at(h);
      
      bool still_inside = true;
      int adder = 1;
      
      while (still_inside) {
        Matrix s_right = extract_matrix(this_coord.row, this_coord.col + adder, 3);
        still_inside = s_right.exceed_threshold(0.6);
        if (set_compare(spatial_coords, Coordinate(this_coord.row, this_coord.col + adder))) {
          spatial_coords.push_back(Coordinate(this_coord.row, this_coord.col + adder));
        }
        adder++;
      }
      
      //printf("  Enter (%d, %d)\n", this_coord.row, this_coord.col);
      //cout << "Leaving right-boundary at " << this_coord.row << ", " << this_coord.col + (adder - 1) << endl;
    }
    
    // now take the top-most pixel, then expand two-dimensionally upwards
//    int min_col = 0XFFFF;
//    int max_col = 0;
//    int min_row = 0xFFFF;
//    for (int s = 0; s < spatial_coords.size(); s++) {
//      Coordinate c = spatial_coords.at(s);
//      if (c.col < min_col) {
//        min_col = c.col;
//      }
//      if (c.col > max_col) {
//        max_col = c.col;
//      }
//      if (c.row < min_row) {
//        min_row = c.row;
//      }
//      
//    }
//    if (min_col != max_col) {
//      for (int c = min_col; c <= max_col; c++) {
//        int subtractor = 1;
//        bool still_inside = true;
//        
//        while (still_inside) {
//          Matrix s_up = extract_matrix(min_row - subtractor, c, 3);
//          still_inside = s_up.exceed_threshold(0.67);
//          
//          if (still_inside) {
//            //spatial_coords.push_back(Coordinate(min_row - subtractor, c));
//          }
//          subtractor++;
//        }
//      }
//    }
    
    spatial_data.push_back(spatial_coords);
  }
  
//  // clean up missing lines
//  vector<bool> _t_line = { 1, 1, 1, 0, 0, 0, 1, 1, 1 };
//  BinaryMatrix t_line = BinaryMatrix(_t_line, 3);
//  for (int i = 0; i < spatial_data.size(); i++) {
//    vector<Coordinate> spatial_row = spatial_data.at(i);
//    vector<Coordinate> new_members = vector<Coordinate>();
//    
//    for (int j = 0; j < spatial_row.size(); j++) {
//      Matrix img = extract_matrix(spatial_row.at(j), 3);
//      bool t_line_match = t_line.match(img);
//      if (t_line_match) {
//        new_members.push_back(spatial_row.at(j));
//      }
//    }
//    
//    for (int nm = 0; nm < new_members.size(); nm++) {
//      spatial_row.push_back(new_members.at(nm));
//    }
//  }
//  
  printf("Grain  Area   Inert C.   X-mnt Y-mnt\n");
  for (int i = 0; i < spatial_data.size(); i++) {
    int row_max = 0;
    int row_min = 0xFFFF;
    int col_max = 0;
    int col_min = 0xFFFF;
    
    for (int s = 0; s < spatial_data.at(i).size(); s++) {
      Coordinate tc = spatial_data.at(i).at(s);
      if (tc.row < row_min) {
        row_min = tc.row;
      }
      if (tc.row > row_max) {
        row_max = tc.row;
      }
      if (tc.col < col_min) {
        col_min = tc.col;
      }
      if (tc.col > col_max) {
        col_max = tc.col;
      }
    }
    int row_length = row_max - row_min + 1;
    int col_length = col_max - col_min + 1;
    int center_row = (row_max + row_min) / 2;
    int center_col = (col_max + col_min) / 2;
    
    printf("%5d  %4ld  (%3d, %3d) %5d %5d\n", i, spatial_data.at(i).size(), center_row, center_col, col_length, row_length);
    
//    printf(" <<< GROUP %d: Area %d >>>\n", i, spatial_data.at(i).size());
//    printf("    Inertia center: %d, %d\n", center_row, center_col);
//    printf("    X-length: %d\n", col_length);
//    printf("    Y-length: %d\n", row_length);
  }
  
  initialize_result(0);
  for (int i = 0; i < spatial_data.size(); i++) {
    vector<Coordinate> tc = spatial_data.at(i);
    
    for (int t = 0; t < tc.size(); t++) {
      Coordinate xc = tc.at(t);
      result_gray->at(xc.row).at(xc.col) = 255;
    }
  }
  
  return spatial_data;
}

Matrix Picture::extract_matrix(Coordinate c, int radius) {
  return extract_matrix(c.row, c.col, radius);
}

Matrix Picture::extract_matrix(int r, int c, int radius) {
  vector<vector<float>> img = vector<vector<float>>();
  
  for (int rr = r - 1; rr <= r + 1; rr++) {
    vector<float> r_img = vector<float>();
    for (int cc = c - 1; cc <= c + 1; cc++) {
      r_img.push_back(data_gray->at(rr).at(cc));
    }
    img.push_back(r_img);
  }
  
  return Matrix(img);
}

void Picture::initialize_result(uint8_t val) {
  if (type == COLOR_GRAY) {
    result_gray = new vector<vector<uint8_t>>();
    
    for (int r = 0; r < dim_y; r++) {
      vector<uint8_t> row_gray = vector<uint8_t>();
      for (int c = 0; c < dim_x; c++) {
        row_gray.push_back(val);
      }
      result_gray->push_back(row_gray);
    }
  } else {
    result = new vector<vector<RgbPixel>*>();
    
    for (int r = 0; r < dim_y; r++) {
      vector<RgbPixel>* row_pixel = new vector<RgbPixel>();
      for (int c = 0; c < dim_x; c++) {
        row_pixel->push_back(RgbPixel(val, val, val));
      }
      result->push_back(row_pixel);
    }
  }
}

void Picture::copy_result_to_data() {
  for (int r = 0; r < dim_y; r++) {
    for (int c = 0; c < dim_x; c++) {
      switch (type) {
        case COLOR_RGB: data->at(r)->at(c) = result->at(r)->at(c); break;
        case COLOR_GRAY: data_gray->at(r).at(c) = result_gray->at(r).at(c); break;
      }
    }
  }
}

void Picture::copy_data_to_result() {
  initialize_result(0);
  
  for (int r = 0; r < dim_y; r++) {
    for (int c = 0; c < dim_x; c++) {
      switch (type) {
        case COLOR_RGB: result->at(r)->at(c) = data->at(r)->at(c); break;
        case COLOR_GRAY: result_gray->at(r).at(c) = data_gray->at(r).at(c); break;
      }
    }  
  }
}

void Picture::write_gray(string out_path) {
  ofstream out;
  out.open(out_path, ios::out | ios::binary);
  
  
  for (auto r = 0; r < result_gray->size(); r++) {
    vector<uint8_t> row_data = result_gray->at(r);
    
    for (auto c = 0; c < row_data.size(); c++) {
      uint8_t byte = row_data.at(c);
      out.write((char*) &byte, sizeof(uint8_t));
    }
  }

  out.close();
  
  cout << "File written to " << out_path << "\n";
}

void Picture::write_gray(string out_path, vector<vector<uint8_t>*> *in) {
  ofstream out;
  out.open(out_path, ios::out | ios::binary);
  
  for (auto r = 0; r < in->size(); r++) {
    vector<uint8_t> *row_data = in->at(r);
    
    for (auto c = 0; c < row_data->size(); c++) {
      uint8_t byte = row_data->at(c);
      out.write((char*) &byte, sizeof(uint8_t));
    }
  }
  
  out.close();
  
  cout << "File written to " << out_path << "\n";
}

void Picture::write_rgb(string out_path) {
  ofstream out;
  out.open(out_path, ios::out | ios::binary);
  
  for (auto r = result->begin(); r != result->end(); ++r) {
    for (auto c = (*r)->begin(); c != (*r)->end(); ++c) {
      out.write((char*) &c->r, sizeof(uint8_t));
      out.write((char*) &c->g, sizeof(uint8_t));
      out.write((char*) &c->b, sizeof(uint8_t));
    }
  }
  
  out.close();
  
  cout << "File written to " << out_path << "\n";
}

void Picture::write_cmyk(string out_path) {
  string out_c = out_path + "_cyan.raw";
  string out_m = out_path + "_magenta.raw";
  string out_y = out_path + "_yellow.raw";
  
  ofstream osc;
  ofstream osm;
  ofstream osy;
  
  osc.open(out_c, ios::out | ios::binary);
  osm.open(out_m, ios::out | ios::binary);
  osy.open(out_y, ios::out | ios::binary);
  
  for (auto r = data_cmyk->begin(); r != data_cmyk->end(); ++r) {
    for (auto c = (*r)->begin(); c != (*r)->end(); ++c) {
      osc.write((char*) &c->c, sizeof(uint8_t));
      osm.write((char*) &c->m, sizeof(uint8_t));
      osy.write((char*) &c->y, sizeof(uint8_t));
    }
  }
  
  osc.close();
  osm.close();
  osy.close();
  
  cout << "File written to " << out_c << "\n";
  cout << "File written to " << out_y << "\n";
  cout << "File written to " << out_m << "\n";
}

void Picture::write_hsl(string out_path) {
  string out_h = out_path + "_hue.raw";
  string out_s = out_path + "_saturation.raw";
  string out_l = out_path + "_lightness.raw";
  
  ofstream osh;
  ofstream oss;
  ofstream osl;
  
  osh.open(out_h, ios::out | ios::binary);
  oss.open(out_s, ios::out | ios::binary);
  osl.open(out_l, ios::out | ios::binary);
  
  for (auto r = data_hsl->begin(); r != data_hsl->end(); ++r) {
    for (auto c = (*r)->begin(); c != (*r)->end(); ++c) {
      osh.write((char*) &c->h, sizeof(uint8_t));
      oss.write((char*) &c->s, sizeof(uint8_t));
      osl.write((char*) &c->l, sizeof(uint8_t));
    }
  }
  
  osh.close();
  oss.close();
  osl.close();
  
  cout << "File written to " << out_h << "\n";
  cout << "File written to " << out_s << "\n";
  cout << "File written to " << out_l << "\n";
}

void Picture::to_cmyk() {
  type = COLOR_CMYK;
  
  data_cmyk = new std::vector<std::vector<CmykPixel>*>();
  std::vector<CmykPixel>* row_data = new std::vector<CmykPixel>();
  
  for (auto r = data->begin(); r != data->end(); ++r) {
    row_data = new std::vector<CmykPixel>();
    for (auto c = (*r)->begin(); c != (*r)->end(); ++c) {
      row_data->push_back(c->to_cmyk());
    }
    
    data_cmyk->push_back(row_data);
  }
}

void Picture::to_hsl() {
  type = COLOR_HSL;
  
  data_hsl = new std::vector<std::vector<HslPixel>*>();
  std::vector<HslPixel>* row_data = new std::vector<HslPixel>();
  
  for (auto r = data->begin(); r != data->end(); ++r) {
    row_data = new std::vector<HslPixel>();
    for (auto c = (*r)->begin(); c != (*r)->end(); ++c) {
      row_data->push_back(c->to_hsl());
    }
    
    data_hsl->push_back(row_data);
  }
}

void Picture::load_rgb() {
  ifstream in(path, std::ios::binary);
  uint8_t _byte;
  uint32_t col_counter = 0;
  uint32_t channel_counter = 0;
  uint32_t byte_counter = 0;
  
  uint8_t channels[3] = {0,0,0};
  
  data = new std::vector<std::vector<RgbPixel>*>();
  std::vector<RgbPixel>* row_data = new std::vector<RgbPixel>();
  
  while (in.read((char*) &_byte, sizeof(_byte))) {
    channel_counter = byte_counter % 3;
    channels[channel_counter] = _byte;
    col_counter = (byte_counter / 3) % dim_x;
    
    // First pixel in row x
    if (col_counter == 0) {
      row_data = new std::vector<RgbPixel>();
    }
    
    channels[channel_counter] = _byte;
    if (channel_counter == 2) {
      RgbPixel pixel = *new RgbPixel(channels[0], channels[1], channels[2]);
      row_data->push_back(pixel);
    }
    
    // Last pixel in row x
    if (col_counter == dim_x - 1 && channel_counter == 2) {
      data->push_back(row_data);
    }
    
    byte_counter++;
  }
}

void Picture::load_gray() {
  ifstream in(path, std::ios::binary);
  uint8_t _byte;
  uint32_t col_counter = 0;
  uint32_t byte_counter = 0;
  
  data_gray = new std::vector<std::vector<uint8_t>>();
  std::vector<uint8_t> row_data = *new std::vector<uint8_t>();
  
  while (in.read((char*) &_byte, sizeof(_byte))) {
    col_counter = byte_counter % dim_x;
    
    if (col_counter == 0) {
      row_data = *new std::vector<uint8_t>();
    }
    
    row_data.push_back(_byte);
    
    if (col_counter == dim_x - 1) {
      data_gray->push_back(row_data);
    }
    
    byte_counter++;
  }
}

uint32_t Picture::get_dim_x() {
  return dim_x;
}

uint32_t Picture::get_dim_y() {
  return dim_y;
}

uint32_t Picture::get_type() {
  return type;
}

vector<vector<RgbPixel>*>* Picture::get_rgb_data() {
  return data;
}