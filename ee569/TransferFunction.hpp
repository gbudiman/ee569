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
  TransferFunction(std::string path, Picture*, Picture*, uint8_t);
  void prepare_gnu_plot();
private:
  void generate_transfer_function_gray();
  
  std::vector<float> *tf_gray;
  std::vector<float> *tf_red;
  std::vector<float> *tf_green;
  std::vector<float> *tf_blue;
  
  Picture *a;
  Picture *b;
  std::string path;
  uint8_t type;
};

#endif /* TransferFunction_hpp */
