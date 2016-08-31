//
//  TransferFunction.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/29/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef TransferFunction_hpp
#define TransferFunction_hpp

#include "main.hpp"
#include "Picture.hpp"

class TransferFunction {
public:
  TransferFunction();
  TransferFunction(uint32_t);
  void generate_linear(int, int, int, int);
  
  std::vector<int16_t> *data;
private:
  void initialize(uint32_t);
};

#endif /* TransferFunction_hpp */
