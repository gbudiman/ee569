//
//  BitStreamMatrix.hpp
//  ee569
//
//  Created by Gloria Budiman on 9/29/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef BitStreamMatrix_hpp
#define BitStreamMatrix_hpp

#include "main.hpp"
#include "BinaryMatrix.hpp"

class BitStreamMatrix {
public:
  static int pack(int, int, int, int, int, int, int, int, int);
  static int pack(BinaryMatrix);
};

#endif /* BitStreamMatrix_hpp */
