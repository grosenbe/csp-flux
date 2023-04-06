#pragma once

#include <array>
#include <memory>
#include <vector>

#include "facet.h"

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

  const std::array<double, 3> &
  GetFieldCoords() { return fieldCoords; }

  double
  GetZOffset() { return zOffset; }
  static double pedistalHeight;

 private:
  const std::array<double, 3> fieldCoords;
  const double zOffset;
};
}  // namespace cspflux
