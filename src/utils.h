#pragma once

#include <eigen3/Eigen/Dense>

#include "../spa/spa.h"

namespace cspflux {
// clang-format off
constexpr double PI    = 3.14159265358979323846;
constexpr double D2R   = PI / 180;
constexpr double R2D   = 180 / PI;
//clang-format on

  bool CompareDoubles(double, double);
  spa_data CreateSpaData();
  Eigen::Vector3d ConvertSpaDataToEnu(const spa_data&);

  Eigen::Matrix3d RotationAboutVector(const Eigen::Vector3d &, double);
}
