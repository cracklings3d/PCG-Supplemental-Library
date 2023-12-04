#include "pch.h"

#include <iostream>

#include "PCG_supplemental_library.h"

std::vector<size_t> PCG_supplemental_library::detect_cluster(std::vector<double> points) {
  std::vector<size_t> val;

  Point_set ps;

  assert(points.size() % 3 == 0);

  for (size_t i = 0; i < points.size(); i += 3) {
    ps.insert(Point_3(points[i], points[i + 1], points[i + 2]));
  }

  auto index_prop_map = _detect_cluster(ps);
  for (auto point : ps.points()) {
    // print (x, y, z) and the index of the point
    // std::cout << point << " " << index_prop_map[point] << std::endl;
    std::cout << point << " " << std::endl;
  }

  auto properties = ps.properties();

  auto index_prop = ps.property_map<size_t>("index");


  assert(points.size() == val.size());
  return val;
}

PCG_supplemental_library::Point_set::Property_map<size_t> PCG_supplemental_library::_detect_cluster(Point_set points) {
  std::vector<Point_set> val;

  Point_set::Property_map<size_t> cluster_map = points.add_property_map<size_t>("cluster id", -1).first;

  double spacing = CGAL::compute_average_spacing<CGAL::Parallel_if_available_tag>(points, 6);
  std::cerr << "Spacing = " << spacing << std::endl;

  std::vector<std::pair<std::size_t, std::size_t>> adjacencies;

  Point_set &clustered_points = points;

  CGAL::Real_timer t;
  t.start();
  std::size_t nb_clusters =
      CGAL::cluster_point_set(clustered_points, cluster_map,
                              // points.parameters().neighbor_radius(spacing).adjacencies(
                              points.parameters().neighbor_radius(200).adjacencies(
                                std::back_inserter(adjacencies)));

  t.stop();
  // cout total time
  std::cerr << "Clustering done in " << t.time() << " sec" << std::endl;

  // Point_set::Property_map<int> point_index = points.add_property_map<int>("index", 0).first;
  // for (Point_set::Index point : points) {
  //   point_index[point] = cluster_map[point];
  // }

  return cluster_map;
}
