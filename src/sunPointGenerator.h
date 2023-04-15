#pragma once

#include <eigen3/Eigen/Dense>

using Eigen::Vector3d;
namespace cspflux {
class sunPointGenerator {
 public:
  sunPointGenerator() = delete;
  virtual Vector3d GenerateSunPoint() = 0;

 protected:
  Vector3d sunCenter;
  double slntRgax;

  std::vector<Vector3d> sunCoordinateBasis;

  sunPointGenerator(const Vector3d &);
};
}  // namespace cspflux
