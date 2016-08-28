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
}

void Picture::write_to_file(string _path) {
  switch(type) {
    case COLOR_RGB: write_rgb(_path); break;
  }
}

void Picture::load() {
  switch(type) {
    case COLOR_RGB: load_rgb(); break;
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
