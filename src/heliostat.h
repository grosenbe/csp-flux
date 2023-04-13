#pragma once

#include <array>
#include <eigen3/Eigen/Dense>
#include <memory>
#include <vector>

#include "facet.h"

using Eigen::Vector3d;
using std::vector;

namespace cspflux {

struct driveAngles {
  double azimuth;
  double elevation;
};

class heliostat {
 public:
  heliostat(double E, double N, double U, double Z);
  heliostat(const heliostat &);

  driveAngles driveAngles{1000, 1000};

  vector<facet> facets;

  const Vector3d &
  GetFieldCoords() { return fieldCoords; }

  double
  GetZOffset() { return zOffset; }
  static double pedistalHeight;

 private:
  const Vector3d fieldCoords;
  const double zOffset;
};
}  // namespace cspflux
