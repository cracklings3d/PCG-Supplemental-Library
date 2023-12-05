#include "pch.h"

#include "../PCG-Supplemental-Library/PCG_point_cloud.h"


TEST(PCG_point_cloud, cluster_analysis) {
  const std::string test_file_path = std::string{SOLUTION_DIR} + "pcg_test.bin";
  PCG_point_cloud   pc             = PCG_point_cloud::parse_file(test_file_path);

  EXPECT_FALSE(pc.points.empty());
  EXPECT_EQ(pc.cluster_id.size(), 0);

  pc.analyze_cluster();

  EXPECT_EQ(pc.points.size(), pc.cluster_id.size());
}
