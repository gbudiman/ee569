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
  int separation_threshold = 8;
  int energy_radius = 21;
  float energy_threshold = 0.3;
  int distance_threshold = 5;
  Picture butterfly = Picture("hw2_images/Butterfly.raw", 335, 320, COLOR_BINARY);
//  butterfly.copy_data_to_result();
//  butterfly.write_to_file("hw2_out/Butterfly_gray.raw");
//  
  //butterfly = Picture("hw2_out/Butterfly_gray.raw", 335, 320, COLOR_GRAY);
  vector<Coordinate> traces = butterfly.trace_boundary();
//
//  butterfly.fill_holes2(traces);
//  butterfly.write_to_file("hw2_out/Butterfly_traced.raw");
//  
  butterfly = Picture("hw2_out/Butterfly_traced.raw", 335, 320, COLOR_GRAY);
//  butterfly.morph(MORPH_THINNING);
//  butterfly.write_to_file("hw2_out/Butterfly_thinning.raw");
//  
//  butterfly = Picture("hw2_out/Butterfly_traced.raw", 335, 320, COLOR_GRAY);
//  butterfly.morph(MORPH_SKELETONIZING);
//  butterfly.write_to_file("hw2_out/Butterfly_skeletonizing.raw");
//  
//  butterfly = Picture("hw2_out/Butterfly_traced.raw", 335, 320, COLOR_GRAY);
//  butterfly.morph(MORPH_SHRINKING);
//  butterfly.write_to_file("hw2_out/Butterfly_shrinking.raw");
  
  //butterfly = Picture("hw2_out/Butterfly_skeletonizing.raw", 335, 320, COLOR_GRAY);
  //butterfly.compute_diagonal_lines(3);
  //butterfly.compute_global_connectivity();
  //butterfly.compute_branching(separation_threshold);
  //butterfly.compute_concentration(sqrt((335.0*320.0)/(496.0*502.0)) * energy_radius, energy_threshold);
  //butterfly.label_connected_components();
  butterfly.label_connected_components(distance_threshold);
  butterfly.write_to_file("hw2_out/Butterfly_labeled.raw");
//
  Picture fly = Picture("hw2_images/Fly.raw", 222,223, COLOR_BINARY);
//  fly.copy_data_to_result();
//  fly.write_to_file("hw2_out/Fly_gray.raw");
//
//  fly = Picture("hw2_out/Fly_gray.raw", 222, 223, COLOR_GRAY);
//  traces = fly.trace_boundary();
//  fly.fill_holes2(traces);
//  fly.write_to_file("hw2_out/Fly_traced.raw");
//  
//  fly = Picture("hw2_out/Fly_traced.raw", 222, 223, COLOR_GRAY);
//  fly.morph(MORPH_THINNING);
//  fly.write_to_file("hw2_out/Fly_thinning.raw");
//  
//  fly = Picture("hw2_out/Fly_traced.raw", 222, 223, COLOR_GRAY);
//  fly.morph(MORPH_SKELETONIZING);
//  fly.write_to_file("hw2_out/Fly_skeletonizing.raw");
//  
  fly = Picture("hw2_out/Fly_traced.raw", 222, 223, COLOR_GRAY);
//  fly.morph(MORPH_SHRINKING);
//  fly.write_to_file("hw2_out/Fly_shrinking.raw");
  
  //fly = Picture("hw2_out/Fly_skeletonizing.raw", 222, 223, COLOR_GRAY);
  //fly.compute_diagonal_lines(3);
  //fly.compute_global_connectivity();
  //fly.compute_branching(separation_threshold);
  //fly.compute_concentration(sqrt((222.0*223.0)/(496.0*502.0)) * energy_radius, energy_threshold);
  fly.label_connected_components(distance_threshold);
  fly.write_to_file("hw2_out/Fly_labeled.raw");
//  
  Picture probe = Picture("hw2_images/Probe.raw", 496,502, COLOR_BINARY);
//  probe.copy_data_to_result();
//  probe.write_to_file("hw2_out/Probe_gray.raw");
//  
  probe = Picture("hw2_out/Probe_gray.raw", 496, 502, COLOR_GRAY);
  traces = probe.trace_boundary();
//  probe.fill_holes2(traces);
//  probe.write_to_file("hw2_out/Probe_traced.raw");
//
  probe = Picture("hw2_out/Probe_traced.raw", 496, 502, COLOR_GRAY);
//  probe.morph(MORPH_THINNING);
//  probe.write_to_file("hw2_out/Probe_thinning.raw");
//  
//  probe = Picture("hw2_out/Probe_traced.raw", 496, 502, COLOR_GRAY);
//  probe.morph(MORPH_SKELETONIZING);
//  probe.write_to_file("hw2_out/Probe_skeletonizing.raw");
//  
//  probe = Picture("hw2_out/Probe_traced.raw", 496, 502, COLOR_GRAY);
//  probe.morph(MORPH_SHRINKING);
//  probe.write_to_file("hw2_out/Probe_shrinking.raw");
  // probe = Picture("hw2_out/Probe_skeletonizing.raw", 496, 502, COLOR_GRAY);
  //probe.compute_diagonal_lines(3);
  //probe.compute_global_connectivity();
  //probe.compute_branching(separation_threshold);
  //probe.compute_concentration(energy_radius, energy_threshold);
  probe.label_connected_components(distance_threshold);
  probe.write_to_file("hw2_out/Probe_labeled.raw");
}
