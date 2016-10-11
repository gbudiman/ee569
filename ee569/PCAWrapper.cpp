//
//  PCAWrapper.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/11/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "PCAWrapper.hpp"
using namespace cv;

PCAWrapper::PCAWrapper(const Mat& pcaset, int max_components, const Mat& testset, Mat& compressed) {
  PCA pca(pcaset, Mat(), PCA::DATA_AS_ROW, max_components);
}