//
//  run_2_3_a_rice_grain.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/22/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"
#include "GrainCategorizer.hpp"

void f_2_3_a_rice_grain() {
//  Picture rg = Picture("hw2_images/Rice.raw", 690, 500, COLOR_RGB);
//  rg.to_grayscale();
//  rg.write_to_file("hw2_out/Rice_gray.raw");
//  
//  Picture rgray = Picture("hw2_out/Rice_gray.raw", 690, 500, COLOR_GRAY);
//  rgray.prepare_gnuplot_histogram_data("hw2_out/Rice_gray.raw", STRIP_EXTENSION);
//  rgray.adaptive_thresholding2(75);
//  rgray.write_to_file("hw2_out/Rice_thresholded.raw");

  Picture rth = Picture("hw2_out/Rice_thresholded.raw", 690, 500, COLOR_GRAY);
  rth.morph(MORPH_THIN);
  rth.write_to_file("hw2_out/Rice_thinning.raw");
  
  rth = Picture("hw2_out/Rice_thresholded.raw", 690, 500, COLOR_GRAY);
  rth.morph(MORPH_ERODE);
  rth.write_to_file("hw2_out/Rice_eroding.raw");
  
//  rth.crop(168, 394, 302, 480); // 135x87
//  rth.write_to_file("hw2_out/Rice_thresholded_cropped.raw");
  
//  Picture rth_small = Picture("hw2_out/Rice_thresholded_cropped.raw", 135, 87, COLOR_GRAY);
//  rth_small.morph_thin();
//  rth_small.write_to_file("hw2_out/Rsmall_thinning.raw");
  
/////////////////////////////////////
// below this line is incorrect
//
//  Picture rth = Picture("hw2_out/Rice_thresholded.raw", 690, 500, COLOR_GRAY);
//  rth.morph_erode();
//  rth.write_to_file("hw2_out/Rice_erode.raw");
//  
//  Picture reroded = Picture("hw2_out/Rice_erode.raw", 690, 500, COLOR_GRAY);
//  reroded.post_process_threshold();
//  reroded.write_to_file("hw2_out/Rice_thrpp.raw");
  
//  Picture rpp = Picture("hw2_out/Rice_thrpp.raw", 690, 500, COLOR_GRAY);
//  rpp.morph_erode();
//  rpp.copy_result_to_data();
//  GrainCategorizer gc = rpp.count_objects();
//  rpp.write_to_file("hw2_out/Rice_counted.raw");
//  
//  rpp = Picture("hw2_out/Rice_thrpp.raw", 690, 500, COLOR_GRAY);
//  rpp.compute_spatial_data(gc);
//  rpp.write_to_file("hw2_out/Rice_expanded.raw");
}
