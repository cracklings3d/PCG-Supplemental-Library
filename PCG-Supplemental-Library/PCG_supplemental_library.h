#pragma once

#include "framework.h"

#include "CGAL/Classification.h"
#include "CGAL/Point_set_3/IO.h"
#include "CGAL/Point_set_3.h"
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/cluster_point_set.h"
#include "CGAL/compute_average_spacing.h"


class PCG_supplemental_library {
private:
  using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
  using Point_3 = CGAL::Point_3<Kernel>;
  using Point_set = CGAL::Point_set_3<Point_3>;

public:
  // Cluster detection algorithm, that marks each point with a cluster id.
  static std::vector<size_t> detect_cluster(std::vector<double> points);

private:
  static Point_set::Property_map<size_t> _detect_cluster(Point_set points);
};
