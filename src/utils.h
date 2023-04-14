#pragma once

#include <eigen3/Eigen/Dense>

#include "../spa/spa.h"

namespace cspflux {
// clang-format off
constexpr double PI    = 3.14159265358979323846;
constexpr double PI_2  = 1.57079632679489661923;
constexpr double PI_4  = 0.78539816339744830962;
constexpr double SQRT2 = 1.41421356237309504880;
//clang-format on

  bool CompareDoubles(double, double);
  spa_data CreateSpaData();
  Eigen::Vector3d ConvertSpaDataToEnu(const spa_data&);
}
