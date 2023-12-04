#include "pch.h"
#include <fstream>

#include "PCG_point_cloud.h"
#include "PCG_supplemental_library.h"


PCG_point_cloud PCG_point_cloud::parse_file(const std::string &file_path) {
  // open file, and simply read sequentially as byte stream. The whole file contains only double floats from start to finish.
  std::ifstream   file(file_path, std::ios::binary);
  PCG_point_cloud val;

  auto file_buf = reinterpret_cast<const double *>(file.rdbuf());
  auto file_size = file.gcount();
  for (int i = 0; i < file.gcount(); ++i) {
  }

  double x, y, z;
  while (file >> x >> y >> z) {
    val.points.push_back(x);
    val.points.push_back(y);
    val.points.push_back(z);
  }

  file.close();
  return val;
}

void PCG_point_cloud::analyze_cluster() {
  cluster_id = PCG_supplemental_library::detect_cluster(points);
}

// overload << for _Point
std::ostream &operator<<(std::ostream &os, const std::array<double, 3> &point) {
  os << std::get<0>(point) << " " << std::get<1>(point) << " " << std::get<2>(point);
  return os;
}

// overload << for vector
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
  for (const auto &v : vec) {
    os << v << std::endl;
  }
  return os;
}

void PCG_point_cloud::write_clustered_result_to_file(const std::string &file_path) const {
  std::ofstream file(file_path, std::ios::binary);

  file << points;
  file << cluster_id;

  file.close();
}
