//
//  Picture.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Picture.hpp"
using namespace std;

Picture::Picture(string _path, uint32_t _dim_x, uint32_t _dim_y, uint32_t _type) {
  path = _path;
  dim_x = _dim_x;
  dim_y = _dim_y;
  type = _type;
  
  load();
  generate_histogram();
}

void Picture::write_to_file(string _path) {
  switch(type) {
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

void Picture::prepare_gnuplot_histogram_data(string out_path) {
  string out_gray_pdf = out_path + "_hist_gray_pdf.txt";
  string out_gray_cdf = out_path + "_hist_gray_cdf.txt";
  
  ofstream osgp, osgc;
  
  switch(type) {
    case COLOR_GRAY:
      osgp.open(out_gray_pdf, ios::out);
      osgc.open(out_gray_cdf, ios::out);
      
      for (int i = 0; i < hist_gray->data->size(); i++) {
        osgp << hist_gray->data->at(i) << "\n";
        osgc << cdf_gray->data->at(i) << "\n";
      }
      break;
    case COLOR_RGB:
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

void Picture::load() {
  switch(type) {
    case COLOR_RGB: load_rgb(); break;
    case COLOR_GRAY: load_gray(); break;
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
        for (auto c = (*r)->begin(); c != (*r)->end(); ++c) {
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
        cdf_green += hist_r->data->at(i);
        cdf_blue += hist_r->data->at(i);
        
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
  
  data_gray = new std::vector<std::vector<uint8_t>*>();
  std::vector<uint8_t>* row_data = new std::vector<uint8_t>();
  
  while (in.read((char*) &_byte, sizeof(_byte))) {
    col_counter = byte_counter % dim_x;
    
    if (col_counter == 0) {
      row_data = new std::vector<uint8_t>();
    }
    
    row_data->push_back(_byte);
    
    if (col_counter == dim_x - 1) {
      data_gray->push_back(row_data);
    }
    
    byte_counter++;
  }
}
