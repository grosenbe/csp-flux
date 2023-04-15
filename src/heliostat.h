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
  const driveAngles&
  GetDriveAngles() { return driveAngles; }

  const Vector3d&
  GetFieldCoords() { return fieldCoords; }

  double
  GetZOffset() { return zOffset; }
  double
  GetFocalLength() { return focalLength; }
  double
  GetFacetGap() { return facetGap; }
  int
  GetNumRows() { return numRows; }
  int
  GetNumCols() { return numCols; }

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

 protected:
  heliostat(double E, double N, double U, double Z, double F, int nRows, int nCols, double fGap);

  const int numRows;
  const int numCols;
  const double facetGap;
};

class heliostat_SR115 : public heliostat {
 public:
  heliostat_SR115(double E, double N, double U, double Z, double F);

 private:
};
}  // namespace cspflux
