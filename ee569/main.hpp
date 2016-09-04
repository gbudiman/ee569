//
//  main.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
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
#include <vector>

#define COLOR_GRAY    0
#define COLOR_RGB     1 // 8-bit RGB
#define COLOR_CMYK    2
#define COLOR_HSL     3

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

#define NLM_H 0.001
#define NLM_H_SQUARED 2.0 * NLM_H * NLM_H

#define RUN_ALL false

#endif /* main_h */
