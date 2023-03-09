#pragma once

#include "facet.h"

#include <array>
#include <memory>
#include <vector>

using std::vector;

struct driveAngles {
  double azimuth;
  double elevation;
};

class heliostat {
public:
  heliostat(double E, double N, double U);

  driveAngles driveAngles;

  vector<std::unique_ptr<facet>> facets;

  static double pedistalHeight;

private:
  [[maybe_unused]] std::array<double, 3> fieldCoords;
};
