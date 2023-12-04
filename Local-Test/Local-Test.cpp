#include <iostream>

#include "../PCG-Supplimental-Library/PCG_point_cloud.h"


int main() {
  PCG_point_cloud pc = PCG_point_cloud::parse_file("D:/SVN_mirror_SH/PCG_Foliage/Saved/pcg_test.bin");

  pc.analyze_cluster();
}
