//
//  run_2_3_b_mpeg7.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/1/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "Picture.hpp"

void f_2_3_b_mpeg7() {
  Picture butterfly = Picture("hw2_images/Butterfly.raw", 335, 320, COLOR_BINARY);
  butterfly.copy_data_to_result();
  butterfly.write_to_file("hw2_out/Butterfly_gray.raw");
  
  butterfly = Picture("hw2_out/Butterfly_gray.raw", 335, 320, COLOR_GRAY);
  vector<Coordinate> traces = butterfly.trace_boundary();
  //butterfly.fill_holes(traces);
  butterfly.fill_holes2(traces);
  butterfly.write_to_file("hw2_out/Butterfly_traced.raw");
  
  Picture fly = Picture("hw2_images/Fly.raw", 222,223, COLOR_BINARY);
  fly.copy_data_to_result();
  fly.write_to_file("hw2_out/Fly_gray.raw");
  
  fly = Picture("hw2_out/Fly_gray.raw", 222, 223, COLOR_GRAY);
  fly.trace_boundary();
  fly.write_to_file("hw2_out/Fly_traced.raw");
  
  Picture probe = Picture("hw2_images/Probe.raw", 496,502, COLOR_BINARY);
  probe.copy_data_to_result();
  probe.write_to_file("hw2_out/Probe_gray.raw");
  
  probe = Picture("hw2_out/Probe_gray.raw", 496, 502, COLOR_GRAY);
  probe.trace_boundary();
  probe.write_to_file("hw2_out/Probe_traced.raw");
}
