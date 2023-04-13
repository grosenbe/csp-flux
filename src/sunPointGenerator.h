#pragma once

#include <eigen3/Eigen/Dense>
#include <random>
#include <vector>

using Eigen::Vector3d;

class sunPointGenerator {
 public:
  sunPointGenerator(const Vector3d &, int = 0);

  std::vector<Vector3d> GenerateSunPoints(int);

 private:
  Vector3d sunCenter;
  std::uniform_real_distribution<> distribution;
  std::default_random_engine engine;
  double slntRgax;

  std::vector<Vector3d> sunCoordinateBasis;
};
