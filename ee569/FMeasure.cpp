//
//  FMeasure.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/17/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "FMeasure.hpp"

FMeasure::FMeasure(Picture _base) {
  base = _base;
  
  dim_x = _base.get_dim_x();
  dim_y = _base.get_dim_y();
  
  result = Picture("", dim_x, dim_y, COLOR_RGB);
}

void FMeasure::compare_against(Picture _other) {
  int false_positive, false_negative, true_positive, true_negative;
  
  result.compare_f_measure(base, _other, true_positive, true_negative, false_negative, false_positive);
  printf("%5.1f%% %5.1f%% %5.1f%% %5.1f%%\n", f_float(true_positive), f_float(true_negative), f_float(false_positive), f_float(false_negative));
  printf("  Precision: %5.2f | Recall: %5.2f\n", f_precision(true_positive, false_positive), f_recall(true_positive, false_negative));
  printf("  F: %5.2f\n", f_compute(true_positive, true_negative, false_positive, false_negative));
}

float FMeasure::f_float(int x) {
  return (float) x * 100 / (float) (dim_x * dim_y);
}

float FMeasure::f_compute(int tp, int tn, int fp, int fn) {
  float precision = f_precision(tp, fp);
  float recall = f_recall(tp, fn);
  
  return 2 * precision * recall / (precision + recall);
}

float FMeasure::f_precision(int tp, int fp) {
  return (float) tp / (float) (tp + fp);
}

float FMeasure::f_recall(int tp, int fn) {
  return (float) tp / (float) (tp + fn);
}