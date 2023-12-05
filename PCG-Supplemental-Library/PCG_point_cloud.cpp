#include "pch.h"
#include <fstream>

#include "PCG_point_cloud.h"
#include "PCG_supplemental_library.h"


PCG_point_cloud PCG_point_cloud::parse_file(const std::string &file_path) {
  // open file, and simply read sequentially as byte stream. The whole file contains only double floats from start to finish.
  std::ifstream        file(file_path, std::ios::binary | std::ios::ate);
  PCG_point_cloud      val;
  const std::streampos file_size = file.tellg();

  std::vector<char> raw_content;
  raw_content.resize(file_size);

  file.seekg(0, std::ios::beg);
  file.read(raw_content.data(), file_size);
  file.close();

  auto d = reinterpret_cast<double *>(raw_content.data());

  val.points.resize(file_size / sizeof(double));
  std::copy_n(d, file_size / sizeof(double), val.points.begin());

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
