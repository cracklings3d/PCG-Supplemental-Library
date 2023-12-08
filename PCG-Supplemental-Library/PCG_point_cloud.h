#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace PSL {
class PCG_point_cloud {
private:
  using _Point = std::array<double, 3>;

public:
  static PCG_point_cloud parse_file(const std::string &file_path);
  void                   analyze_cluster();

  void write_clustered_result_to_file(const std::string &file_path) const;

  std::vector<size_t> cluster_id;
  std::vector<double> points;
};
}
