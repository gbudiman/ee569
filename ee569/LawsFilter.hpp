//
//  LawsFilter.hpp
//  ee569
//
//  Created by Gloria Budiman on 10/10/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef LawsFilter_hpp
#define LawsFilter_hpp

#include "Matrix.hpp"

class LawsFilter {
public:
  LawsFilter();
  
  std::vector<Matrix> filter_banks;
private:
  void generate_filter_banks();
};
#endif /* LawsFilter_hpp */
