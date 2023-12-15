#pragma once

#include "PSL_framework.h"

#include <vector>


namespace PSL {
class PSL_LIBRARY Clustering {
public:
  static std::vector<size_t> detect_cluster(const std::vector<double> &points);
};
}
