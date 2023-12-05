#include <iostream>

#include "../PCG-Supplemental-Library/PCG_point_cloud.h"


int main()
{
  std::string test_file_path = std::string{SOLUTION_DIR} + "pcg_test.bin";
  PCG_point_cloud pc = PCG_point_cloud::parse_file(test_file_path);
  // get ${SolutionDir}pcg_test.bin


  pc.analyze_cluster();
}
