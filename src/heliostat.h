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
  heliostat(double E, double N, double U, double Z, double F);
  heliostat(const heliostat &);

  const driveAngles &
  GetDriveAngles() { return driveAngles; }

  const Vector3d &
  GetFieldCoords() { return fieldCoords; }

  double
  GetZOffset() { return zOffset; }
  double
  GetFocalLength() { return focalLength; }

  static double pedistalHeight;

  void
  SetAzimuth(double azimuth) { driveAngles.azimuth = azimuth; }
  void
  SetElevation(double elevation) { driveAngles.elevation = elevation; }

  vector<facet> facets;

 private:
  const Vector3d fieldCoords;
  const double zOffset;
  const double focalLength;

  driveAngles driveAngles{1000, 1000};
};
}  // namespace cspflux
