//
//  Picture.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
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
  if (strip_extension) {
    uint32_t dot_position = (uint32_t) _path.find_last_of('.');
    write_to_file(_path.substr(0, dot_position));
  } else {
    write_to_file(_path);
  }
}

void Picture::prepare_gnuplot_transfer_function(string out_path) {
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
  type = hist_type;
  dim_x = x;
  dim_y = y;
  switch(hist_type) {
    case COLOR_GRAY:
      hist_gray = h;
      cdf_gray = new Histogram();
      generate_cdf_from_histogram(CHANNEL_GRAY);
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
      
      remap_histogram_rgb(tf_red, tf_green, tf_blue);
      
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

void Picture::remap_histogram_gray(std::vector<int16_t> *luteq) {
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
