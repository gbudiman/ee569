//
//  RgbPixel.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "RgbPixel.hpp"
using namespace std;

RgbPixel::RgbPixel(uint8_t _r, uint8_t _g, uint8_t _b) {
  r = _r;
  g = _g;
  b = _b;
}

CmykPixel RgbPixel::to_cmyk() {
  uint8_t c = 255 - r;
  uint8_t m = 255 - g;
  uint8_t y = 255 - b;
  
  CmykPixel cp = *new CmykPixel(c, m, y);
  return cp;
}

HslPixel RgbPixel::to_hsl() {
  double pct_r = (double) r / 255;
  double pct_g = (double) g / 255;
  double pct_b = (double) b / 255;
  
  double smax = std::max({pct_r, pct_g, pct_b});
  double smin = std::min({pct_r, pct_g, pct_b});
  
  double hue = (smax + smin) / 2;
  double saturation = (smax + smin) / 2;
  double lightness = (smax + smin) / 2;
  
  if (smax == smin) {
    hue = 0;
    saturation = 0;
  } else {
    double mid_c = smax - smin;
    if (lightness > 0.5) {
      saturation = mid_c / (2 - smax - smin);
    } else {
      saturation = mid_c / (smax + smin);
    }
    
    if (smax == pct_r) {
      hue = (pct_g - pct_b) / mid_c + ( pct_g < pct_b ? 6 : 0 );
    } else if (smax == pct_g) {
      hue = (pct_b - pct_r) / mid_c + 2;
    } else if (smax == pct_b) {
      hue = (pct_r - pct_g) / mid_c + 4;
    }
    
    hue = hue / 6;
  }
  
  
  HslPixel hp = *new HslPixel(hue * 255, saturation * 255, lightness * 255);
  return hp;
}