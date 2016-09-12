//
//  run_1_3_b_cascaded_filter.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/9/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"

void f_1_3_b_cascaded_filter() {
  Picture* buildings = new Picture("images/P3/Buildings_noisy.raw", 512, 512, COLOR_RGB);
  buildings->apply_median_filter(3, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  buildings->write_to_file("images/P3/Buildings_median_3.raw");
  
  Picture* buildings_median_3 = new Picture("images/P3/Buildings_median_3.raw", 512, 512, COLOR_RGB);
  buildings_median_3->apply_mean_filter(3, FILTER_RED | FILTER_GREEN | FILTER_BLUE );
  buildings_median_3->write_to_file("images/P3/Buildings_median_3_mean_3.raw");
  
  Picture* base = new Picture("images/P3/Buildings_median_3_mean_3.raw", 512, 512, COLOR_RGB);
  base->apply_nlm_filter(7, 3, 0.001);
  base->write_to_file("images/P3/Buildings_stack_nlm_7_3.raw");
  base->apply_nlm_filter(7, 5, 0.001);
  base->write_to_file("images/P3/Buildings_stack_nlm_7_5.raw");
  base->apply_nlm_filter(15, 3, 0.001);
  base->write_to_file("images/P3/Buildings_stack_nlm_15_3.raw");
  base->apply_nlm_filter(15, 5, 0.001);
  base->write_to_file("images/P3/Buildings_stack_nlm_15_5.raw");
}
