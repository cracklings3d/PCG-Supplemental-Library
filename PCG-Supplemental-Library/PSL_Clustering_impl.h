#pragma once

#include "PSL_domain.h"
#include "framework.h"


namespace PSL {
class Clustering_impl {
public:
  static Point_set detect_cluster(Point_set points);
};
}
