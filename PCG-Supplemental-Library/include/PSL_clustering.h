#pragma once

#include <string>
#include <vector>


namespace PSL {
class Clustering_impl;

class Clustering {
public:
  static std::vector<size_t> detect_cluster(std::vector<double> points);
};
}
