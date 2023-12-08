#include "pch.h"
#include <vector>

#include "PSL_clustering_impl.h"
#include "include/PSL_clustering.h"
#include "PSL_domain.h"


std::vector<size_t> PSL::Clustering::detect_cluster(std::vector<double> points) {
  std::vector<size_t> val;

  PSL::Point_set ps;

  assert(points.size() % 3 == 0);

  for (size_t i = 0; i < points.size(); i += 3) {
    ps.insert(PSL::Point_3(points[i], points[i + 1], points[i + 2]));
  }

  auto clustered_points = PSL::Clustering_impl::detect_cluster(ps);

  const size_t *d = clustered_points.property_map<size_t>("cluster id").first.data();
  // copy from d to val
  std::copy_n(d, points.size(), std::back_inserter(val));

  assert(points.size() == val.size());
  return val;
}
