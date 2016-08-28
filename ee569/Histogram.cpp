//
//  Histogram.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/28/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Histogram.hpp"

Histogram::Histogram() {
  data = new std::vector<uint32_t>();
  
  for (uint16_t i = 0; i < 256; i++) {
    data->push_back(0);
  }
}

void Histogram::push(uint8_t value) {
  data->at(value)++;
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
  uint8_t max_rows = 64;
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