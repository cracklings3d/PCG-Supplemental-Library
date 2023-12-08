#pragma once

#include "PSL_decl.h"

#include <string>
#include <vector>


namespace PSL {
class Clustering_impl;

class PSL_LIBRARY Clustering {
public:
  static std::vector<size_t> detect_cluster(std::vector<double> points);
};
}
