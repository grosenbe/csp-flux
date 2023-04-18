#pragma once

#include <array>
#include <eigen3/Eigen/Dense>
#include <memory>
#include <vector>

#include "facet.h"

using namespace Eigen;
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
  const Matrix3d&
  GetHeliostatToEnuTransform();

  const Vector3d&
  GetFieldCoords() { return fieldCoords; }

  double
  GetAimOffset() { return aimOffset; }
  double
  GetFocalLength() { return focalLength; }
  double
  GetFacetGap() { return facetGap; }
  int
  GetNumRows() { return numRows; }
  int
  GetNumCols() { return numCols; }
  const vector<facet>&
  GetFacets() { return facets; }

  static double pedistalHeight;

  void
  SetAzimuth(double azimuth) { driveAngles.azimuth = azimuth; }
  void
  SetElevation(double elevation) { driveAngles.elevation = elevation; }
  void
  SetHeliostatToEnuTransform(const Matrix3d& transform) { heliostatToEnuTransform = transform; }

  void ComputeTransforms(const Vector3d&);

 private:
  vector<facet> facets;
  const Vector3d fieldCoords;
  const double aimOffset;
  const double focalLength;

  driveAngles driveAngles{1000, 1000};

  Matrix3d heliostatToEnuTransform;

 protected:
  heliostat(double E, double N, double U, double Z, double F, int nRows, int nCols, double fGap);

  const int numRows;
  const int numCols;
  const double facetGap;
};

class heliostat_115m2 : public heliostat {
 public:
  heliostat_115m2(double E, double N, double U, double Z, double F);

 private:
};
}  // namespace cspflux
