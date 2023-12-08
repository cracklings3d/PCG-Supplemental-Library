#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_3.h>
#include <CGAL/Point_set_3.h>


namespace PSL {
using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point_3 = CGAL::Point_3<Kernel>;
using Point_set = CGAL::Point_set_3<Point_3>;
}
