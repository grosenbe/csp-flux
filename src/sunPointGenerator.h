#pragma once

#include <eigen3/Eigen/Dense>

using Eigen::Vector3d;
namespace cspflux {
class sunPointGenerator {
 public:
  sunPointGenerator(const Vector3d &);

  virtual std::vector<Vector3d> GenerateSunPoints(int) = 0;

 protected:
  Vector3d sunCenter;
  double slntRgax;

  std::vector<Vector3d> sunCoordinateBasis;
};
}  // namespace cspflux
