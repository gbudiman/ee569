//
//  Psnr.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/3/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef Psnr_hpp
#define Psnr_hpp

#include "main.hpp"
#include "Picture.hpp"
#include "RgbPixel.hpp"

class Psnr {
public:
  Psnr(Picture*, Picture*);
  void compute();
private:
  Picture *a;
  Picture *b;
};

#endif /* Psnr_hpp */
