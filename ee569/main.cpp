//
//  main.cpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "main.hpp"
#include "project_inclusion.hpp"
using namespace std;

int main() {
  int debug = 1;

  switch(debug) {
    case 0: f_1_1_a_cropping(); break;
    case 1: f_1_1_a_resizing(); break;
  }
  
  return 0;
}