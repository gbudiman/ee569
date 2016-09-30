//
//  MorphMatrix.cpp
//  ee569
//
//  Created by Gloria Budiman on 9/28/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "MorphMatrix.hpp"

MorphMatrix::MorphMatrix() {
  thinning = vector<BinaryMatrix>();
  shrinking = vector<BinaryMatrix>();
  skeletonizing = vector<BinaryMatrix>();
  
  thinning_bitstream = vector<int>();
  shrinking_bitstream = vector<int>();
  skeletonizing_bitstream = vector<int>();
  
  
  BinaryMatrix b_1a1 = BinaryMatrix(0, 0, 1, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_1a2 = BinaryMatrix(1, 0, 0, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_1a3 = BinaryMatrix(0, 0, 0, 0, 1, 0, 1, 0, 0);
  BinaryMatrix b_1a4 = BinaryMatrix(0, 0, 0, 0, 1, 0, 0, 0, 1);
  
  BinaryMatrix b_2a1 = BinaryMatrix(0, 0, 0, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_2a2 = BinaryMatrix(0, 1, 0, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_2a3 = BinaryMatrix(0, 0, 0, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_2a4 = BinaryMatrix(0, 0, 0, 0, 1, 0, 0, 1, 0);
  
  BinaryMatrix b_3a1 = BinaryMatrix(0, 0, 1, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_3a2 = BinaryMatrix(0, 1, 1, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_3a3 = BinaryMatrix(1, 1, 0, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_3a4 = BinaryMatrix(1, 0, 0, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_3a5 = BinaryMatrix(0, 0, 0, 1, 1, 0, 1, 0, 0);
  BinaryMatrix b_3a6 = BinaryMatrix(0, 0, 0, 0, 1, 0, 1, 1, 0);
  BinaryMatrix b_3a7 = BinaryMatrix(0, 0, 0, 0, 1, 0, 0, 1, 1);
  BinaryMatrix b_3a8 = BinaryMatrix(0, 0, 0, 0, 1, 1, 0, 0, 1);
  
  BinaryMatrix b_4a1 = BinaryMatrix(0, 1, 0, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_4a2 = BinaryMatrix(0, 1, 0, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_4a3 = BinaryMatrix(0, 0, 0, 1, 1, 0, 0, 1, 0);
  BinaryMatrix b_4a4 = BinaryMatrix(0, 0, 0, 0, 1, 1, 0, 1, 0);
  
  BinaryMatrix b_4b1 = BinaryMatrix(0, 0, 1, 0, 1, 1, 0, 0, 1);
  BinaryMatrix b_4b2 = BinaryMatrix(1, 1, 1, 0, 1, 0, 0, 0, 0);
  BinaryMatrix b_4b3 = BinaryMatrix(1, 0, 0, 1, 1, 0, 1, 0, 0);
  BinaryMatrix b_4b4 = BinaryMatrix(0, 0, 0, 0, 1, 0, 1, 1, 1);
  
  BinaryMatrix b_5a1 = BinaryMatrix(1, 1, 0, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_5a2 = BinaryMatrix(0, 1, 0, 0, 1, 1, 0, 0, 1);
  BinaryMatrix b_5a3 = BinaryMatrix(0, 1, 1, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_5a4 = BinaryMatrix(0, 0, 1, 0, 1, 1, 0, 1, 0);
  
  BinaryMatrix b_5b1 = BinaryMatrix(0, 1, 1, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_5b2 = BinaryMatrix(1, 1, 0, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_5b3 = BinaryMatrix(0, 0, 0, 1, 1, 0, 1, 1, 0);
  BinaryMatrix b_5b4 = BinaryMatrix(0, 0, 0, 0, 1, 1, 0, 1, 1);
  
  BinaryMatrix b_6a1 = BinaryMatrix(1, 1, 0, 0, 1, 1, 0, 0, 1);
  BinaryMatrix b_6a2 = BinaryMatrix(0, 1, 1, 1, 1, 0, 1, 0, 0);
  
  BinaryMatrix b_6b1 = BinaryMatrix(1, 1, 1, 0, 1, 1, 0, 0, 0);
  BinaryMatrix b_6b2 = BinaryMatrix(0, 1, 1, 0, 1, 1, 0, 0, 1);
  BinaryMatrix b_6b3 = BinaryMatrix(1, 1, 1, 1, 1, 0, 0, 0, 0);
  BinaryMatrix b_6b4 = BinaryMatrix(1, 1, 0, 1, 1, 0, 1, 0, 0);
  BinaryMatrix b_6b5 = BinaryMatrix(1, 0, 0, 1, 1, 0, 1, 1, 0);
  BinaryMatrix b_6b6 = BinaryMatrix(0, 0, 0, 1, 1, 0, 1, 1, 1);
  BinaryMatrix b_6b7 = BinaryMatrix(0, 0, 0, 0, 1, 1, 1, 1, 1);
  BinaryMatrix b_6b8 = BinaryMatrix(0, 0, 1, 0, 1, 1, 0, 1, 1);
  
  BinaryMatrix b_7a1 = BinaryMatrix(1, 1, 1, 0, 1, 1, 0, 0, 1);
  BinaryMatrix b_7a2 = BinaryMatrix(1, 1, 1, 1, 1, 0, 1, 0, 0);
  BinaryMatrix b_7a3 = BinaryMatrix(1, 0, 0, 1, 1, 0, 1, 1, 1);
  BinaryMatrix b_7a4 = BinaryMatrix(0, 0, 1, 0, 1, 1, 1, 1, 1);
  
  BinaryMatrix b_8a1 = BinaryMatrix(0, 1, 1, 0, 1, 1, 0, 1, 1);
  BinaryMatrix b_8a2 = BinaryMatrix(1, 1, 1, 1, 1, 1, 0, 0, 0);
  BinaryMatrix b_8a3 = BinaryMatrix(1, 1, 0, 1, 1, 0, 1, 1, 0);
  BinaryMatrix b_8a4 = BinaryMatrix(0, 0, 0, 1, 1, 1, 1, 1, 1);
  
  BinaryMatrix b_9a1 = BinaryMatrix(1, 1, 1, 0, 1, 1, 0, 1, 1);
  BinaryMatrix b_9a2 = BinaryMatrix(0, 1, 1, 0, 1, 1, 1, 1, 1);
  BinaryMatrix b_9a3 = BinaryMatrix(1, 1, 1, 1, 1, 1, 1, 0, 0);
  BinaryMatrix b_9a4 = BinaryMatrix(1, 1, 1, 1, 1, 1, 0, 0, 1);
  BinaryMatrix b_9a5 = BinaryMatrix(1, 1, 1, 1, 1, 0, 1, 1, 0);
  BinaryMatrix b_9a6 = BinaryMatrix(1, 1, 0, 1, 1, 0, 1, 1, 1);
  BinaryMatrix b_9a7 = BinaryMatrix(1, 0, 0, 1, 1, 1, 1, 1, 1);
  BinaryMatrix b_9a8 = BinaryMatrix(0, 0, 1, 1, 1, 1, 1, 1, 1);
  
  BinaryMatrix b_10a1 = BinaryMatrix(1, 1, 1, 0, 1, 1, 1, 1, 1);
  BinaryMatrix b_10a2 = BinaryMatrix(1, 1, 1, 1, 1, 1, 1, 0, 1);
  BinaryMatrix b_10a3 = BinaryMatrix(1, 1, 1, 1, 1, 0, 1, 1, 1);
  BinaryMatrix b_10a4 = BinaryMatrix(1, 0, 1, 1, 1, 1, 1, 1, 1);
  
  BinaryMatrix b_11a1 = BinaryMatrix(1, 1, 1, 1, 1, 1, 0, 1, 1);
  BinaryMatrix b_11a2 = BinaryMatrix(1, 1, 1, 1, 1, 1, 1, 1, 0);
  BinaryMatrix b_11a3 = BinaryMatrix(1, 1, 0, 1, 1, 1, 1, 1, 1);
  BinaryMatrix b_11a4 = BinaryMatrix(0, 1, 1, 1, 1, 1, 1, 1, 1);
  
  // MarkPatternMatrix(MCZ, MCZ, MCZ, MCZ, MCZ, MCZ, MCZ, MCZ, MCZ);
  
  MarkPatternMatrix m_spur1 = MarkPatternMatrix(MCZ, MCZ, MCM, MCZ, MCM, MCZ, MCZ, MCZ, MCZ);
  MarkPatternMatrix m_spur2 = MarkPatternMatrix(MCM, MCZ, MCZ, MCZ, MCM, MCZ, MCZ, MCZ, MCZ);
  MarkPatternMatrix m_s4c1  = MarkPatternMatrix(MCZ, MCZ, MCZ, MCZ, MCM, MCZ, MCZ, MCM, MCZ);
  MarkPatternMatrix m_s4c2  = MarkPatternMatrix(MCZ, MCZ, MCZ, MCZ, MCM, MCM, MCZ, MCZ, MCZ);
  
  MarkPatternMatrix m_lcl1  = MarkPatternMatrix(MCZ, MCZ, MCM, MCZ, MCM, MCM, MCZ, MCZ, MCZ);
  MarkPatternMatrix m_lcl2  = MarkPatternMatrix(MCZ, MCM, MCM, MCZ, MCM, MCZ, MCZ, MCZ, MCZ);
  MarkPatternMatrix m_lcl3  = MarkPatternMatrix(MCM, MCM, MCZ, MCZ, MCM, MCZ, MCZ, MCZ, MCZ);
  MarkPatternMatrix m_lcl4  = MarkPatternMatrix(MCM, MCZ, MCZ, MCM, MCM, MCZ, MCZ, MCZ, MCZ);
  MarkPatternMatrix m_lcl5  = MarkPatternMatrix(MCZ, MCZ, MCZ, MCM, MCM, MCZ, MCM, MCZ, MCZ);
  MarkPatternMatrix m_lcl6  = MarkPatternMatrix(MCZ, MCZ, MCZ, MCZ, MCM, MCZ, MCM, MCM, MCZ);
  MarkPatternMatrix m_lcl7  = MarkPatternMatrix(MCZ, MCZ, MCZ, MCZ, MCM, MCZ, MCZ, MCM, MCM);
  MarkPatternMatrix m_lcl8  = MarkPatternMatrix(MCZ, MCZ, MCZ, MCZ, MCM, MCM, MCZ, MCZ, MCM);
  
  MarkPatternMatrix m_4c01  = MarkPatternMatrix(MCZ, MCM, MCM, MCM, MCM, MCZ, MCZ, MCZ, MCZ);
  MarkPatternMatrix m_4c02  = MarkPatternMatrix(MCM, MCM, MCZ, MCZ, MCM, MCM, MCZ, MCZ, MCZ);
  MarkPatternMatrix m_4c03  = MarkPatternMatrix(MCZ, MCM, MCZ, MCZ, MCM, MCM, MCZ, MCZ, MCM);
  MarkPatternMatrix m_4c04  = MarkPatternMatrix(MCZ, MCZ, MCM, MCZ, MCM, MCM, MCZ, MCM, MCZ);
  
  MarkPatternMatrix m_scc1  = MarkPatternMatrix(MCZ, MCA, MCM, MCZ, MCM, MCB, MCM, MCZ, MCZ);
  MarkPatternMatrix m_scc2  = MarkPatternMatrix(MCM, MCB, MCZ, MCA, MCM, MCZ, MCZ, MCZ, MCM);
  MarkPatternMatrix m_scc3  = MarkPatternMatrix(MCZ, MCZ, MCM, MCA, MCM, MCZ, MCM, MCB, MCZ);
  MarkPatternMatrix m_scc4  = MarkPatternMatrix(MCM, MCZ, MCZ, MCZ, MCM, MCB, MCZ, MCA, MCM);
  
  MarkPatternMatrix m_cc    = MarkPatternMatrix(MCM, MCM, MCD, MCM, MCM, MCD, MCD, MCD, MCD);
  
  MarkPatternMatrix m_teb1  = MarkPatternMatrix(MCD, MCM, MCZ, MCM, MCM, MCM, MCD, MCZ, MCZ);
  MarkPatternMatrix m_teb2  = MarkPatternMatrix(MCZ, MCM, MCD, MCM, MCM, MCM, MCZ, MCZ, MCD);
  MarkPatternMatrix m_teb3  = MarkPatternMatrix(MCZ, MCZ, MCD, MCM, MCM, MCM, MCZ, MCM, MCD);
  MarkPatternMatrix m_teb4  = MarkPatternMatrix(MCD, MCZ, MCZ, MCM, MCM, MCM, MCD, MCM, MCZ);
  MarkPatternMatrix m_teb5  = MarkPatternMatrix(MCD, MCM, MCD, MCM, MCM, MCZ, MCZ, MCM, MCZ);
  MarkPatternMatrix m_teb6  = MarkPatternMatrix(MCZ, MCM, MCZ, MCM, MCM, MCZ, MCD, MCM, MCD);
  MarkPatternMatrix m_teb7  = MarkPatternMatrix(MCZ, MCM, MCZ, MCZ, MCM, MCM, MCD, MCM, MCD);
  MarkPatternMatrix m_teb8  = MarkPatternMatrix(MCD, MCM, MCD, MCZ, MCM, MCM, MCZ, MCM, MCZ);
  
  MarkPatternMatrix m_veb1  = MarkPatternMatrix(MCM, MCD, MCM, MCD, MCM, MCD, MCA, MCB, MCC);
  MarkPatternMatrix m_veb2  = MarkPatternMatrix(MCM, MCD, MCC, MCD, MCM, MCB, MCM, MCD, MCA);
  MarkPatternMatrix m_veb3  = MarkPatternMatrix(MCC, MCB, MCA, MCD, MCM, MCD, MCM, MCD, MCM);
  MarkPatternMatrix m_veb4  = MarkPatternMatrix(MCA, MCD, MCM, MCB, MCM, MCD, MCC, MCD, MCM);
  
  MarkPatternMatrix m_dgb1  = MarkPatternMatrix(MCD, MCM, MCZ, MCZ, MCM, MCM, MCM, MCZ, MCD);
  MarkPatternMatrix m_dgb2  = MarkPatternMatrix(MCZ, MCM, MCD, MCM, MCM, MCZ, MCD, MCZ, MCM);
  MarkPatternMatrix m_dgb3  = MarkPatternMatrix(MCD, MCZ, MCM, MCM, MCM, MCZ, MCZ, MCM, MCD);
  MarkPatternMatrix m_dgb4  = MarkPatternMatrix(MCM, MCZ, MCD, MCZ, MCM, MCM, MCD, MCM, MCZ);
  
  shrinking.push_back(b_1a1);
  shrinking.push_back(b_1a2);
  shrinking.push_back(b_1a3);
  shrinking.push_back(b_1a4);
  shrinking.push_back(b_2a1);
  shrinking.push_back(b_2a2);
  shrinking.push_back(b_2a3);
  shrinking.push_back(b_2a4);
  shrinking.push_back(b_3a1);
  shrinking.push_back(b_3a2);
  shrinking.push_back(b_3a3);
  shrinking.push_back(b_3a4);
  shrinking.push_back(b_3a5);
  shrinking.push_back(b_3a6);
  shrinking.push_back(b_3a7);
  shrinking.push_back(b_3a8);
  
  thinning.push_back(b_4a1);
  thinning.push_back(b_4a2);
  thinning.push_back(b_4a3);
  thinning.push_back(b_4a4);
  skeletonizing.push_back(b_4a1);
  skeletonizing.push_back(b_4a2);
  skeletonizing.push_back(b_4a3);
  skeletonizing.push_back(b_4a4);
  
  shrinking.push_back(b_4b1);
  shrinking.push_back(b_4b2);
  shrinking.push_back(b_4b3);
  shrinking.push_back(b_4b4);
  thinning.push_back(b_4b1);
  thinning.push_back(b_4b2);
  thinning.push_back(b_4b3);
  thinning.push_back(b_4b4);
  skeletonizing.push_back(b_4b1);
  skeletonizing.push_back(b_4b2);
  skeletonizing.push_back(b_4b3);
  skeletonizing.push_back(b_4b4);
  
  shrinking.push_back(b_5a1);
  shrinking.push_back(b_5a2);
  shrinking.push_back(b_5a3);
  shrinking.push_back(b_5a4);
  thinning.push_back(b_5a1);
  thinning.push_back(b_5a2);
  thinning.push_back(b_5a3);
  thinning.push_back(b_5a4);
  shrinking.push_back(b_5b1);
  shrinking.push_back(b_5b2);
  shrinking.push_back(b_5b3);
  shrinking.push_back(b_5b4);
  thinning.push_back(b_5b1);
  thinning.push_back(b_5b2);
  thinning.push_back(b_5b3);
  thinning.push_back(b_5b4);
  
  shrinking.push_back(b_6a1);
  shrinking.push_back(b_6a2);
  thinning.push_back(b_6a1);
  thinning.push_back(b_6a2);
  
  shrinking.push_back(b_6b1);
  shrinking.push_back(b_6b2);
  shrinking.push_back(b_6b3);
  shrinking.push_back(b_6b4);
  shrinking.push_back(b_6b5);
  shrinking.push_back(b_6b6);
  shrinking.push_back(b_6b7);
  shrinking.push_back(b_6b8);
  thinning.push_back(b_6b1);
  thinning.push_back(b_6b2);
  thinning.push_back(b_6b3);
  thinning.push_back(b_6b4);
  thinning.push_back(b_6b5);
  thinning.push_back(b_6b6);
  thinning.push_back(b_6b7);
  thinning.push_back(b_6b8);
  skeletonizing.push_back(b_6b1);
  skeletonizing.push_back(b_6b2);
  skeletonizing.push_back(b_6b3);
  skeletonizing.push_back(b_6b4);
  skeletonizing.push_back(b_6b5);
  skeletonizing.push_back(b_6b6);
  skeletonizing.push_back(b_6b7);
  skeletonizing.push_back(b_6b8);
  
  shrinking.push_back(b_7a1);
  shrinking.push_back(b_7a2);
  shrinking.push_back(b_7a3);
  shrinking.push_back(b_7a4);
  thinning.push_back(b_7a1);
  thinning.push_back(b_7a2);
  thinning.push_back(b_7a3);
  thinning.push_back(b_7a4);
  skeletonizing.push_back(b_7a1);
  skeletonizing.push_back(b_7a2);
  skeletonizing.push_back(b_7a3);
  skeletonizing.push_back(b_7a4);
  
  shrinking.push_back(b_8a1);
  shrinking.push_back(b_8a2);
  shrinking.push_back(b_8a3);
  shrinking.push_back(b_8a4);
  thinning.push_back(b_8a1);
  thinning.push_back(b_8a2);
  thinning.push_back(b_8a3);
  thinning.push_back(b_8a4);
  skeletonizing.push_back(b_8a1);
  skeletonizing.push_back(b_8a2);
  skeletonizing.push_back(b_8a3);
  skeletonizing.push_back(b_8a4);
  
  shrinking.push_back(b_9a1);
  shrinking.push_back(b_9a2);
  shrinking.push_back(b_9a3);
  shrinking.push_back(b_9a4);
  shrinking.push_back(b_9a5);
  shrinking.push_back(b_9a6);
  shrinking.push_back(b_9a7);
  shrinking.push_back(b_9a8);
  thinning.push_back(b_9a1);
  thinning.push_back(b_9a2);
  thinning.push_back(b_9a3);
  thinning.push_back(b_9a4);
  thinning.push_back(b_9a5);
  thinning.push_back(b_9a6);
  thinning.push_back(b_9a7);
  thinning.push_back(b_9a8);
  skeletonizing.push_back(b_9a1);
  skeletonizing.push_back(b_9a2);
  skeletonizing.push_back(b_9a3);
  skeletonizing.push_back(b_9a4);
  skeletonizing.push_back(b_9a5);
  skeletonizing.push_back(b_9a6);
  skeletonizing.push_back(b_9a7);
  skeletonizing.push_back(b_9a8);
  
  shrinking.push_back(b_10a1);
  shrinking.push_back(b_10a2);
  shrinking.push_back(b_10a3);
  shrinking.push_back(b_10a4);
  thinning.push_back(b_10a1);
  thinning.push_back(b_10a2);
  thinning.push_back(b_10a3);
  thinning.push_back(b_10a4);
  skeletonizing.push_back(b_10a1);
  skeletonizing.push_back(b_10a2);
  skeletonizing.push_back(b_10a3);
  skeletonizing.push_back(b_10a4);
  
  skeletonizing.push_back(b_11a1);
  skeletonizing.push_back(b_11a2);
  skeletonizing.push_back(b_11a3);
  skeletonizing.push_back(b_11a4);
  
  stump.push_back(m_spur1);
  stump.push_back(m_spur2);
  stump.push_back(m_s4c1);
  stump.push_back(m_s4c2);
  stump.push_back(m_lcl1);
  stump.push_back(m_lcl2);
  stump.push_back(m_lcl3);
  stump.push_back(m_lcl4);
  stump.push_back(m_lcl5);
  stump.push_back(m_lcl6);
  stump.push_back(m_lcl7);
  stump.push_back(m_lcl8);
  stump.push_back(m_4c01);
  stump.push_back(m_4c02);
  stump.push_back(m_4c03);
  stump.push_back(m_4c04);
  stump.push_back(m_scc1);
  stump.push_back(m_scc2);
  stump.push_back(m_scc3);
  stump.push_back(m_scc4);
  stump.push_back(m_cc);
  stump.push_back(m_teb1);
  stump.push_back(m_teb2);
  stump.push_back(m_teb3);
  stump.push_back(m_teb4);
  stump.push_back(m_teb5);
  stump.push_back(m_teb6);
  stump.push_back(m_teb7);
  stump.push_back(m_teb8);
  stump.push_back(m_veb1);
  stump.push_back(m_veb2);
  stump.push_back(m_veb3);
  stump.push_back(m_veb4);
  stump.push_back(m_dgb1);
  stump.push_back(m_dgb2);
  stump.push_back(m_dgb3);
  stump.push_back(m_dgb4);
  
  for (int i = 0; i < thinning.size(); i++) {
    thinning_bitstream.push_back(BitStreamMatrix::pack(thinning.at(i)));
  }
  
  for (int i = 0; i < skeletonizing.size(); i++) {
    skeletonizing_bitstream.push_back(BitStreamMatrix::pack(skeletonizing.at(i)));
  }
  
  for (int i = 0; i < shrinking.size(); i++) {
    shrinking_bitstream.push_back(BitStreamMatrix::pack(shrinking.at(i)));
  }
}

void MorphMatrix::debug_matrix(int type) {
  vector<BinaryMatrix> v;
  
  switch(type) {
    case MORPH_THINNING: v = thinning; break;
    case MORPH_SHRINKING: v = shrinking; break;
    case MORPH_SKELETONIZING: v = skeletonizing; break;
  }
  
  for (int i = 0; i < v.size(); i++) {
    v.at(i).debug_3x3();
  }
}

void MorphMatrix::debug_type2_filter() {
  for (int i = 0; i < stump.size(); i++) {
    stump.at(i).debug_3x3();
  }
}

//int MorphMatrix::thinning_hit_or_miss(Matrix img) {
//  //int pixel_value = img.data.at(1).at(1) > 127 ? 255 : 0;
//  if (thinning_first_filter(img)) {
//    return MCM;
//  }
//  
//  return MCZ;
//}

bool MorphMatrix::thinning_first_filter(int img_bts) {
  for (int i = 0; i < thinning_bitstream.size(); i++) {
    if (thinning_bitstream.at(i) == img_bts) { return true; };
  }
  
  return false;
}

bool MorphMatrix::skeletonizing_first_filter(int img_bts) {
  for (int i = 0; i < skeletonizing_bitstream.size(); i++) {
    if (skeletonizing_bitstream.at(i) == img_bts) { return true; };
  }
  
  return false;
}

bool MorphMatrix::eroding_first_filter(int img_bts) {
  for (int i = 0; i < shrinking_bitstream.size(); i++) {
    if (shrinking_bitstream.at(i) == img_bts) { return true; };
  }
  
  return false;
}

bool MorphMatrix::thinning_unconditional_filter(Matrix img, Matrix mask) {
  for (int i = 0; i < stump.size(); i++) {
    MarkPatternMatrix mpmx = stump.at(i);
    bool is_matched = mpmx.match(img, mask);
    
    if (is_matched) {
      return true;
    }
  }
  
  return false;
}

bool MorphMatrix::eroding_unconditional_filter(Matrix img, Matrix mask) {
  for (int i = 0; i < stump.size(); i++) {
    MarkPatternMatrix mpmx = stump.at(i);
    bool is_matched = mpmx.match(img, mask);
    
    if (is_matched) {
      return true;
    }
  }
  
  return false;
}

bool MorphMatrix::skeletonizing_unconditional_filter(Matrix img, Matrix mask) {

  
  return false;
}
