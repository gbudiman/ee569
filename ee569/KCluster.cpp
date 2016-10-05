//
//  KCluster.cpp
//  ee569
//
//  Created by Gloria Budiman on 10/5/16.
//  Copyright © 2016 gbudiman. All rights reserved.
//

#include "KCluster.hpp"
using namespace std;

struct pair_value_sorter {
  inline bool operator() (const pair<Coordinate, float>& s1, const pair<Coordinate, float>& s2) {
    return (s1.second > s2.second);
  }
};

KCluster::KCluster(vector<pair<Coordinate, float>> _raw, int _target_group, float _dev_step) {
  target_group = _target_group;
  deviation_step = _dev_step;
  raw = _raw;
  data = vector<vector<pair<Coordinate, float>>>();
  sort(raw.begin(), raw.end(), pair_value_sorter());
}

void KCluster::categorize() {
  float deviation = ((raw.front().second + raw.back().second) / (target_group));
  int group_count = 0;
  
  while(group_count != target_group) {
    data = vector<vector<pair<Coordinate, float>>>();
    for (int i = 0; i < raw.size(); i++) {
      add(raw.at(i), deviation / 2);
    }
    
    group_count = data.size();
    printf("Deviation %.2f, groups %d\n", deviation, group_count);
    
    if (group_count < target_group) {
      deviation -= deviation_step;
    } else {
      deviation += deviation_step;
    }
  }
  
  debug();
}

void KCluster::add(pair<Coordinate, float> a, float d) {
  if (data.size() == 0) {
    vector<pair<Coordinate, float>> new_vector = vector<pair<Coordinate, float>>();
    new_vector.push_back(a);
    data.push_back(new_vector);
  } else {
    bool is_categorized = false;
    for (int i = 0; i < data.size(); i++) {
      bool is_within_margin = within_margin_at(i, a.second, d);
      
      if (is_within_margin) {
        is_categorized = true;
        data.at(i).push_back(a);
        break;
      }
    }
    
    if (!is_categorized) {
      vector<pair<Coordinate, float>> new_vector = vector<pair<Coordinate, float>>();
      new_vector.push_back(a);
      data.push_back(new_vector);
    }
  }
}

bool KCluster::within_margin_at(int i, float data, float margin) {
  float average = average_at(i);
  return abs(average - data) < margin;
}

float KCluster::average_at(int i) {
  int count = 0;
  float cumulative = 0;
  for (int j = 0; j < data.at(i).size(); j++) {
    cumulative += data.at(i).at(j).second;
    count++;
  }
  
  return cumulative / count;
}

void KCluster::debug() {
  for (int i = 0; i < data.size(); i++) {
    printf("Group %d ===  (%3d members)\n", i, data.at(i).size());
    for (int j = 0; j < data.at(i).size(); j++) {
      printf("  %5.4f\n", data.at(i).at(j).second);
    }
  }
}