//
//  main.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Finalized on 9/12/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef main_h
#define main_h

#include <algorithm>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <thread>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/highgui/highgui.hpp>

#define COLOR_GRAY    0
#define COLOR_RGB     1 // 8-bit RGB
#define COLOR_CMYK    2
#define COLOR_HSL     3
#define COLOR_BINARY  4

#define HEAVY_DEBUG   0

#define CMYK_CYAN     0
#define CMYK_MAGENTA  1
#define CMYK_YELLOW   2

#define CHANNEL_RED   0
#define CHANNEL_GREEN 1
#define CHANNEL_BLUE  2
#define CHANNEL_GRAY  3

#define EQUALIZE_CDF      0
#define EQUALIZE_LINEAR   1

#define STRIP_EXTENSION true

#define SFX_CURVING 0
#define SFX_MATCHING_PREVIOUS 1
#define SFX_MATCHING_FORMULA 2

#define MAX_SQUARED pow(255, 2)
#define FILTER_RED 0x1
#define FILTER_GREEN 0x10
#define FILTER_BLUE 0x100

#define NLM_SEARCH_RADIUS 15
#define NLM_PATCH_RADIUS 3
#define NLM_H 0.001 // 0.001 // don't use 0.01
#define NLM_H_SQUARED 2.0 * NLM_H * NLM_H

#define RUN_ALL 0

#define DIAMOND_REGION_A 0
#define DIAMOND_REGION_B 1
#define DIAMOND_REGION_C 2
#define DIAMOND_REGION_D 3

#define SCAN_OUTSIDE_IMAGE 0
#define SCAN_INSIDE_IMAGE 1

#define DITHER_2 0
#define DITHER_4 1
#define DITHER_4A 2
#define DITHER_8 3
#define DITHER_FSB 4
#define DITHER_JJN 5
#define DITHER_STUCKI 6

#define GAMMA_MID_POINT 102

#define GRAIN_BORDER_THRESHOLD 5
#define GRAIN_AREA_THRESHOLD 20

#define MORPH_THINNING 0
#define MORPH_SHRINKING 1
#define MORPH_SKELETONIZING 2

// Filter type 2
#define MCA 1
#define MCB 2
#define MCC 3
#define MCD 4
#define MCM 5
#define MCZ 0

#define MORPH_THIN 0
#define MORPH_ERODE 1
#define MORPH_SKEL 2

#define MEASURE_CHROMA 1

#define SCAN_DIR_RIGHT 0
#define SCAN_DIR_DOWN 1
#define SCAN_DIR_LEFT 2
#define SCAN_DIR_UP 3

bool xcmp(char*, const char*);
void print_help();
std::vector<std::string> expand_filter_names(std::vector<std::string>);

#endif /* main_h */
