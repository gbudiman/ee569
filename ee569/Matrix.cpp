//
//  Matrix.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/20/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "Matrix.hpp"
using namespace std;

Matrix::Matrix(vector<vector<float>> x) {
  data = x;
}

Matrix::Matrix(vector<float> x, int col) {
  data = vector<vector<float>>();
  vector<float> row_data = vector<float>();
  
  for (int i = 0; i < x.size(); i++) {
    row_data.push_back(x.at(i));
    
    if (i % col == col - 1) {
      data.push_back(row_data);
      row_data = vector<float>();
    }
  }
}

Matrix Matrix::transpose() {
  vector<vector<float>> staging_vectors;
  
  unsigned long dim_y = data.size();
  unsigned long dim_x = data.at(0).size();
  
  staging_vectors = vector<vector<float>>(dim_x);
  for (int r = 0; r < staging_vectors.size(); r++) {
    staging_vectors.at(r) = vector<float>(dim_y);
  }
  
  for (int r = 0; r < dim_y; r++) {
    for (int c = 0; c < dim_x; c++) {
      staging_vectors.at(c).at(r) = data.at(r).at(c);
    }
  }
  
  Matrix new_matrix = Matrix(staging_vectors);
  return new_matrix;
}

Matrix Matrix::multiply(Matrix other) {
  vector<vector<float>> result = vector<vector<float>>();
  //printf("Current: [%lu x %lu]\n", data.size(), data.at(0).size());
  //printf("Other  : [%lu x %lu]\n", other.data.size(), other.data.at(0).size());
  unsigned long result_row_length = data.size(); //other.data.size();
  unsigned long result_col_length = other.data.at(0).size();
  
  for (int row = 0; row < result_row_length; row++) {
    vector<float> row_data = vector<float>();
    for (int col = 0; col < result_col_length; col++) {
      row_data.push_back(0);
    }
    result.push_back(row_data);
  }
  
//  for (int iter_a = 0; iter_a < result_col_length; iter_a++) {
//    for (int iter_b = 0; iter_b < result_row_length; iter_b++) {
//      float acc = 0;
//      for (int iter_c = iter_b; iter_c <= iter_b; iter_c++) {
//        for (int iter_d = 0; iter_d < result_row_length; iter_d++) {
//          printf("([%d, %d] = [%d, %d] X [%d, %d]\n", iter_a, iter_b, iter_c, iter_d, iter_d, iter_a);
//          acc += data.at(iter_b).at(iter_d) * other.data.at(iter_d).at(iter_a);
//        }
//        
//        //acc += data.at(iter_b).at(iter_c) * other.data.at(iter_c).at(iter_b);
//      }
//      
//      result.at(iter_b).at(iter_a) = acc;
//    }
//  }
  
  for (int ia = 0; ia < data.size(); ia++) {
    for (int ic = 0; ic < other.data.at(0).size(); ic++) {
      float acc = 0;
      for (int ib = 0; ib < data.at(0).size(); ib++) {
        //printf("  # [%d, %d] x [%d, %d]\n", ic, ib, ib, ia);
        acc += data.at(ic).at(ib) * other.data.at(ib).at(ia);
      }
      //printf("Save to [%d, %d]\n", ic, ia);
      result.at(ic).at(ia) = acc;
    }
  }
  
  return Matrix(result);
}

float Matrix::multiply_and_average(Matrix other) {
  Matrix res = multiply(other);
  float acc = 0;
  int row_size = res.data.size();
  int col_size = res.data.at(0).size();
  
  for (int row = 0; row < row_size; row++) {
    for (int col = 0; col < col_size; col++) {
      acc += res.data.at(row).at(col);
    }
  }
  
  return acc / (row_size * col_size / 2);
}

void Matrix::thresholdize() {
  int row_size = data.size();
  int col_size = data.at(0).size();
  int n_squared = row_size * col_size;
  
  for (int r = 0; r < row_size; r++) {
    for (int c = 0; c < col_size; c++) {
      data.at(r).at(c) = (data.at(r).at(c) + 0.5) * 255.0 / n_squared;
    }
  }
}

int Matrix::erode(Matrix image) {
  int row_size = data.size();
  int col_size = data.at(0).size();
  
  for (int r = 0; r < row_size; r++) {
    for (int c = 0; c < col_size; c++) {
      if (data.at(r).at(c) > 0.5) {
        // foreground is white == 255
        // anything less than that is background
        if (image.data.at(r).at(c) < 127) {
          return 0;
        }
      }
    }
  }
  
  return 255;
}

bool Matrix::exceed_threshold(float threshold) {
  auto row_count = data.size();
  auto col_count = data.at(0).size();
  
  auto total_cells = row_count * col_count;
  int high_cell = 0;
  
  for (int r = 0; r < row_count; r++) {
    for (int c = 0; c < col_count; c++) {
      if (data.at(r).at(c) > 127) {
        high_cell++;
      }
    }
  }
  
  return (((float) high_cell / (float) total_cells) > threshold);
}