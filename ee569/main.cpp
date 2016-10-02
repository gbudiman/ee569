//
//  main.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "project_inclusion.hpp"
using namespace std;

int main(int argc, char* argv[]) {
  // Main entry
  // Set debug to value between 0 to 12 to run each function separately
  // without command line arguments
  int debug = 26;

  if (RUN_ALL) {
    f_1_1_a_cropping();
    f_1_1_a_resizing();
    f_1_1_b_cmyk();
    f_1_1_b_hsl();
    f_1_2_a_histogram_equalization();
    f_1_2_b_histcolor_equalization();
    f_1_2_c_sfx();
    f_1_2_d_histogram_transform();
    f_1_3_a_median_filtering();
    f_1_3_a_cascaded_filter();
    f_1_3_b_nlm();
  } else {
    switch(debug) {
      case 0: f_1_1_a_cropping(); break;
      case 1: f_1_1_a_resizing(); break;
      case 2: f_1_1_b_cmyk(); break;
      case 3: f_1_1_b_hsl(); break;
      case 4: f_1_2_a_histogram_equalization(); break;
      case 5: f_1_2_b_histcolor_equalization(); break;
      case 6: f_1_2_c_sfx(); break;
      case 7: f_1_2_d_histogram_transform(); break;
      case 8: f_1_3_a_median_filtering(); break;
      case 9: f_1_3_b_nlm(); break;
      case 10: f_1_3_a_cascaded_filter(); break;
      case 11: f_1_3_b_cascaded_filter(); break;
      case 12: f_1_3_psnr_calculator(); break;
        
      case 21: f_2_1_a_diamond_warp(); break;
      case 22: f_2_1_b_puzzle_matching(); break;
      case 23: f_2_1_c_homography(); break;
      case 24: f_2_2_a_dithering(); break;
      case 25: f_2_3_a_rice_grain(); break;
      case 26: f_2_3_b_mpeg7(); break;
    }
    
    return 0;
  }

  // Entry point when debug is disabled
  // This will process command line arguments and call appropriate functions
  // accodring to input arguments
  if (argc < 2) {
    print_help();
    return -1;
  }
  
  if (xcmp(argv[1], "crop")) {
    if (argc != 11) {
      cout << "Usage: main crop <source_img> <dim_x> <dim_y> <color> <output_img> <x1> <y1> <x2> <y2>" << endl
      << "Example: main crop source.raw 300 400 1 out.raw 25 25 89 89" << endl << endl
      << "source_img     : path to raw source image" << endl
      << "dim_x          : source image x dimension" << endl
      << "dim_y          : source image y dimension" << endl
      << "color          : 1 for RGB, 0 for grayscale" << endl
      << "output_img     : path to output image" << endl
      << "x1, y1, x2, y2 : (x1, y1) (x2, y2) cropping point" << endl << endl;
      
      return -1;
    }
    int x, y, mode, x1, y1, x2, y2;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    sscanf(argv[7], "%d", &x1);
    sscanf(argv[8], "%d", &y1);
    sscanf(argv[9], "%d", &x2);
    sscanf(argv[10], "%d", &y2);
    f_crop(argv[2], x, y, mode, argv[6], x1, y1, x2, y2);
  } else if (xcmp(argv[1], "resize")) {
    if (argc != 9) {
      cout << "Usage: main resize <source_img> <dim_x> <dim_y> <color> <out_x> <out_y>" << endl
      << "Example: main resize source.raw 300 400 1 out.raw 800 800" << endl << endl
      << "source_img     : path to raw source image" << endl
      << "dim_x          : source image x dimension" << endl
      << "dim_y          : source image y dimension" << endl
      << "color          : 1 for RGB, 0 for grayscale" << endl
      << "output_img     : path to output image" << endl
      << "out_x, out_y   : (out_x, out_y) target output dimension" << endl << endl;
      
      return -1;
    }
    int x, y, mode, ox, oy;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    sscanf(argv[7], "%d", &ox);
    sscanf(argv[8], "%d", &oy);
    f_resize(argv[2], x, y, mode, argv[6], ox, oy);
  } else if (xcmp(argv[1], "rgb2cmy")) {
    if (argc != 7) {
      cout << "Usage: main rgb2cmy <source_img> <dim_x> <dim_y> <color> <output_img>" << endl
      << "Example: main rgb2cmy source.raw 300 400 1 out.raw" << endl << endl
      << "source_img     : path to raw source image" << endl
      << "dim_x          : source image x dimension" << endl
      << "dim_y          : source image y dimension" << endl
      << "color          : 1 for RGB, 0 for grayscale" << endl
      << "output_img     : path to output image (3 images will be created with channel name appended to each of them)" << endl << endl;
      
      return -1;
    }
    
    int x, y, mode;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    f_cmyk(argv[2], x, y, mode, argv[6]);
  } else if (xcmp(argv[1], "rgb2hsl")) {
    if (argc != 7) {
      cout << "Usage: main rgb2hsl <source_img> <dim_x> <dim_y> <color> <output_img>" << endl
      << "Example: main rgb2hsl source.raw 300 400 1 out.raw" << endl << endl
      << "source_img     : path to raw source image" << endl
      << "dim_x          : source image x dimension" << endl
      << "dim_y          : source image y dimension" << endl
      << "color          : 1 for RGB, 0 for grayscale" << endl
      << "output_img     : path to output image (3 images will be created with channel name appended to each of them)" << endl << endl;
      
      return -1;
    }
    
    int x, y, mode;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    f_hsl(argv[2], x, y, mode, argv[6]);
  } else if (xcmp(argv[1], "hist_equalize_linear")) {
    if (argc != 7) {
      cout << "Usage: main hist_equalize_linear <source_img> <dim_x> <dim_y> <color> <output_img>" << endl
      << "Example: main hist_equalize_linear source.raw 300 400 1 out.raw" << endl << endl
      << "source_img     : path to raw source image" << endl
      << "dim_x          : source image x dimension" << endl
      << "dim_y          : source image y dimension" << endl
      << "color          : 1 for RGB, 0 for grayscale" << endl
      << "output_img     : path to output image" << endl << endl
      << "Raw histogram data will be generated at source's and output's relative location" << endl
      << "Transfer function will be generated at source's relative location" << endl;
      
      return -1;
    }
    
    int x, y, mode;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    f_histogram_equalization(argv[2], x, y, mode, argv[6], EQUALIZE_LINEAR);
  } else if (xcmp(argv[1], "hist_equalize_cdf")) {
    if (argc != 7) {
      cout << "Usage: main hist_equalize_cdf <source_img> <dim_x> <dim_y> <color> <output_img>" << endl
      << "Example: main hist_equalize_cdf source.raw 300 400 1 out.raw" << endl << endl
      << "source_img     : path to raw source image" << endl
      << "dim_x          : source image x dimension" << endl
      << "dim_y          : source image y dimension" << endl
      << "color          : 1 for RGB, 0 for grayscale" << endl
      << "output_img     : path to output image" << endl << endl
      << "Raw histogram data will be generated at source's and output's relative location" << endl;
      
      return -1;
    }
    int x, y, mode;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    f_histogram_equalization(argv[2], x, y, mode, argv[6], EQUALIZE_CDF);
  } else if (xcmp(argv[1], "sfx")) {
    if (argc != 9) {
      cout << "Usage: main sfx <source_img> <dim_x> <dim_y> <reference_img> <ref_x> <ref_y> <output_img>" << endl
      << "Example: main sfx source.raw 300 400 ref.raw 700 800 out.raw" << endl << endl
      << "source_img     : path to raw source image" << endl
      << "dim_x          : source image x dimension" << endl
      << "dim_y          : source image y dimension" << endl
      << "reference_img  : reference image to based the special effect on" << endl
      << "ref_x          : reference image x dimension" << endl
      << "ref_y          : reference image y dimension" << endl
      << "output_img     : path to output image" << endl << endl
      << "Raw histogram data will be generated at source's and output's relative location" << endl;
      
      return -1;
    }
    
    int ix, iy, rx, ry;
    sscanf(argv[3], "%d", &ix);
    sscanf(argv[4], "%d", &iy);
    sscanf(argv[6], "%d", &rx);
    sscanf(argv[7], "%d", &ry);
    f_sfx(argv[2], ix, iy, argv[5], rx, ry, argv[8]);
  } else if (xcmp(argv[1], "hist_match")) {
    if (argc != 9) {
      cout << "Usage: main hist_match <source_img> <dim_x> <dim_y> <color> <output_img> <mean> <distribution>" << endl
      << "Example: main hist_match source.raw 300 400 1 out.raw 125 40" << endl << endl
      << "source_img     : path to raw source image" << endl
      << "dim_x          : source image x dimension" << endl
      << "dim_y          : source image y dimension" << endl
      << "color          : 1 for RGB, 0 for grayscale" << endl
      << "output_img     : path to output image" << endl
      << "mean           : Gaussian\'s mean" << endl
      << "distribution   : Gaussian\'s distribution" << endl << endl
      << "Raw histogram data will be generated at source's and output's relative location" << endl;
      
      return -1;
    }
    int x, y, mode, mean, dist;
    sscanf(argv[3], "%d", &x);
    sscanf(argv[4], "%d", &y);
    sscanf(argv[5], "%d", &mode);
    sscanf(argv[7], "%d", &mean);
    sscanf(argv[8], "%d", &dist);
    f_hist_match(argv[2], x, y, mode, argv[6], mean, dist);
  } else if (xcmp(argv[1], "denoise")) {
    if (argc < 3) {
      cout << "Use any of the following filters:" << endl
      << "  mean" << endl
      << "  median" << endl
      << "  gaussian" << endl
      << "  nlm" << endl << endl
      << "Example: main denoise nlm" << endl;
      
      return -1;
    }
    int x, y, mode, arg1;
    sscanf(argv[4], "%d", &x);
    sscanf(argv[5], "%d", &y);
    sscanf(argv[6], "%d", &mode);
    sscanf(argv[8], "%d", &arg1);
    if (xcmp(argv[2], "mean")) {
      if (argc != 9) {
        cout << "Usage: main denoise mean <source_img> <dim_x> <dim_y> <color> <output_img> <window_size>" << endl
        << "Example: main denoise mean source.raw 300 400 1 out.raw 3" << endl << endl
        << "source_img     : path to raw source image" << endl
        << "dim_x          : source image x dimension" << endl
        << "dim_y          : source image y dimension" << endl
        << "color          : 1 for RGB, 0 for grayscale" << endl
        << "output_img     : path to output image" << endl
        << "window_size    : window size in pixels" << endl << endl
        << "Window size of 3 will create a 3x3 filter" << endl;
        
        return -1;
      }
      f_denoise_mean(argv[3], x, y, mode, argv[7], arg1);
    } else if (xcmp(argv[2], "median")) {
      if (argc != 9) {
        cout << "Usage: main denoise median <source_img> <dim_x> <dim_y> <color> <output_img> <window_size>" << endl
        << "Example: main denoise median source.raw 300 400 1 out.raw 3" << endl << endl
        << "source_img     : path to raw source image" << endl
        << "dim_x          : source image x dimension" << endl
        << "dim_y          : source image y dimension" << endl
        << "color          : 1 for RGB, 0 for grayscale" << endl
        << "output_img     : path to output image" << endl
        << "window_size    : window size in pixels" << endl << endl
        << "Window size of 3 will create a 3x3 filter" << endl;
        
        return -1;
      }
      f_denoise_median(argv[3], x, y, mode, argv[7], arg1);
    } else if (xcmp(argv[2], "gaussian")) {
      if (argc != 10) {
        cout << "Usage: main denoise gaussian <source_img> <dim_x> <dim_y> <color> <output_img> <radius> <sigma>" << endl
        << "Example: main denoise gaussian source.raw 300 400 1 out.raw 2 2" << endl << endl
        << "source_img     : path to raw source image" << endl
        << "dim_x          : source image x dimension" << endl
        << "dim_y          : source image y dimension" << endl
        << "color          : 1 for RGB, 0 for grayscale" << endl
        << "output_img     : path to output image" << endl
        << "radius         : filter radius in pixels" << endl
        << "sigma          : Gaussian distribution factor (can be supplied in floating point)" << endl << endl
        << "Radius of 1 will create a 3x3 filter, of 2 a 5x5, of 3 a 7x7 and so on" << endl;
        
        return -1;
      }
      float arg2;
      sscanf(argv[9], "%f", &arg2);
      f_denoise_gaussian(argv[3], x, y, mode, argv[7], arg1, arg2);
    } else if (xcmp(argv[2], "nlm")) {
      if (argc != 11) {
        cout << "Usage: main denoise nlm <source_img> <dim_x> <dim_y> <color> <output_img> <search_radius> <window_radius> <decay_factor" << endl
        << "Example: main denoise nlm source.raw 300 400 1 out.raw 7 3 1000" << endl << endl
        << "source_img     : path to raw source image" << endl
        << "dim_x          : source image x dimension" << endl
        << "dim_y          : source image y dimension" << endl
        << "color          : 1 for RGB, 0 for grayscale" << endl
        << "output_img     : path to output image" << endl
        << "search_radius  : search radius in pixels" << endl
        << "window_radius  : window radius in pixels" << endl
        << "decay_factor   : dissimilarity decay factor (can be supplied in floating point)" << endl << endl;
        
        return -1;
      }
      int arg2;
      float arg3;
      sscanf(argv[9], "%d", &arg2);
      sscanf(argv[10], "%f", &arg3);
      f_denoise_nlm(argv[3], x, y, mode, argv[7], arg1, arg2, arg3);
    }
  } else if (xcmp(argv[1], "psnr")) {
    if (argc != 7) {
      cout << "Usage: main psnr <source_img> <output_img> <dim_x> <dim_y> <color>" << endl
      << "Example: main denoise gaussian source.raw 300 400 1 out.raw 2 2" << endl << endl
      << "source_img     : path to raw source image" << endl
      << "output_img     : path to output image" << endl
      << "dim_x          : source image x dimension" << endl
      << "dim_y          : source image y dimension" << endl
      << "color          : 1 for RGB, 0 for grayscale" << endl << endl;
      
      return -1;
    }
    int x, y, mode;
    sscanf(argv[4], "%d", &x);
    sscanf(argv[5], "%d", &y);
    sscanf(argv[6], "%d", &mode);
    f_psnr(argv[2], argv[3], x, y, mode);
  } else {
    print_help();
  }
  
  return 0;
}

bool xcmp(char* a, const char* b) {
  // syntactic sugar for string comparison
  return (strcmp(a, b) == 0);
}

void print_help() {
  cout << "Use any of the following options to show usage example:" << endl
  << "  crop" << endl
  << "  resize" << endl
  << "  rgb2cmy" << endl
  << "  rgb2hsl" << endl
  << "  hist_equalize_linear" << endl
  << "  hist_equalize_cdf" << endl
  << "  sfx" << endl
  << "  hist_match" << endl
  << "  denoise" << endl
  << "  psnr" << endl << endl
  << "Example: main denoise" << endl;
}