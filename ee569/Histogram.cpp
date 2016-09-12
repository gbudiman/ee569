//
//  Histogram.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/28/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Histogram.hpp"
using namespace std;

Histogram::Histogram() {
  data = new std::vector<uint32_t>();
  
  for (uint16_t i = 0; i < 256; i++) {
    data->push_back(0);
  }
}

void Histogram::push(uint8_t value) {
  data->at(value)++;
}

void Histogram::update_at(uint8_t index, uint32_t value) {
  data->at(index) = value;
}

void Histogram::debug() {
  for (uint16_t i = 0; i < 256; i++) {
    printf("%.3d: %.7d\n", i, data->at(i));
  }
}

void Histogram::plot() {
  plot(4);
}

void Histogram::plot(uint8_t bucket_size) {
  uint8_t max_rows = 32;
  uint32_t cumulative = 0;
  uint32_t peak = 0;
  std::vector<uint32_t> *buckets = new std::vector<uint32_t>();
  std::vector<std::vector<char>> textplot = *new std::vector<std::vector<char>>();
  
  for (uint16_t i = 0; i < 256; i++) {
    cumulative += data->at(i);
    
    if (i % bucket_size == bucket_size - 1) {
      uint32_t average = cumulative / bucket_size;
      if (average > peak) {
        peak = average;
      }
      buckets->push_back(average);
      cumulative = 0;
    }
  }
  
  for (uint8_t rows = max_rows; rows > 0; rows--) {
    std::vector<char> row_data = *new std::vector<char>();
    for (auto i = buckets->begin(); i != buckets->end(); ++i) {
      float scaled = ((float) *i / (float) peak) * max_rows;
      if (scaled <= rows) {
        row_data.push_back(' ');
      } else {
        float rounded = floor(scaled);
        float diff = scaled - rounded;
        
        if (rounded == rows) {
          if (diff < 0.25) {
            row_data.push_back('|');
          } else if (diff < 0.5) {
            row_data.push_back('i');
          } else if (diff < 0.75) {
            row_data.push_back(':');
          } else {
            row_data.push_back('.');
          }
        } else {
          row_data.push_back('|');
        }
      }
    }
    
    textplot.push_back(row_data);
  }
  
  for (auto r = textplot.begin(); r != textplot.end(); ++r) {
    for (auto c = (*r).begin(); c != (*r).end(); ++c) {
      printf("%c", *c);
    }
    printf("\n");
  }

  for (int i = 0; i < 256 / bucket_size; i++) {
    printf("-");
  }
  
  printf("\n");
}

void Histogram::generate_gaussian(uint32_t mu, uint32_t delta, uint32_t dim_x, uint32_t dim_y) {
  const float pi = 3.1415927;
  const uint32_t pixel_count = dim_x * dim_y;
  vector<float> *unscaled = new vector<float>(256);
  float peak = 0;
  float unscaled_cdf = 0;
  uint32_t cdf = 0;
  
  for (uint32_t i = 0; i < 256; i++) {
    float t1 = 1.0f / sqrt(2 * pi * delta);
    float t2_up = pow(((int32_t) i - (int32_t) mu), 2.0);
    float t2_bot = 2 * pow(delta, 2);
    float t2 = t2_up / t2_bot;
    float t = t1 * exp(-t2);
    
    if (t > peak) {
      peak = t;
    }
    
    unscaled->at(i) = t;
    unscaled_cdf += t;
  }
  
  for (int i = 0; i < unscaled->size(); i++) {
    data->at(i) = round(unscaled->at(i) / unscaled_cdf * pixel_count);
    cdf += data->at(i);
  }
  
  if (HEAVY_DEBUG) {
    printf("Unscaled CDF: %f\n", unscaled_cdf);
    printf("CDF: %d / %d\n", cdf, pixel_count);
  }
}

void Histogram::rescale(float scale) {
  // Rescale to fit target CDF using the provided scale as scaling factor
  uint32_t cdf = 0;
  for (int i = 0; i < data->size(); i++) {
    uint32_t rescaled_value = data->at(i) * scale;
    data->at(i) = rescaled_value;
  }
}