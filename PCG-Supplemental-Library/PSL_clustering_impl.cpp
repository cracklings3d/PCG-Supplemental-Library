#include "pch.h"

#include <iostream>

#include <CGAL/compute_average_spacing.h>
#include <CGAL/Real_timer.h>
#include <CGAL/cluster_point_set.h>

#include "PSL_domain.h"
#include "PSL_Clustering_impl.h"


PSL::Point_set PSL::Clustering_impl::detect_cluster(Point_set points) {
  Point_set::Property_map<size_t> cluster_map = points.add_property_map<size_t>("cluster id", -1).first;

  const double spacing = CGAL::compute_average_spacing<CGAL::Parallel_if_available_tag>(points, 12);
  std::cerr << "Spacing = " << spacing << std::endl;

  Point_set &clustered_points = points;

  CGAL::Real_timer t;
  t.start();
  std::size_t nb_clusters = CGAL::cluster_point_set(clustered_points, cluster_map);
  t.stop();
  std::cerr << "Clustering done in " << t.time() << " sec" << std::endl;

return clustered_points;
}
