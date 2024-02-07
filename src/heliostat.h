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
  GetDriveAngles() const { return driveAngles; }
  const Matrix3d&
  GetHeliostatToEnuTransform() const;

  const Vector3d&
  GetFieldCoords() const { return fieldCoords; }

  double
  GetAimOffset() const { return aimOffset; }
  double
  GetFocalLength() const { return focalLength; }
  double
  GetFacetGap() const { return facetGap; }
  int
  GetNumRows() const { return numRows; }
  int
  GetNumCols() const { return numCols; }
  const vector<facet>&
  GetFacets() const { return facets; }
  int
  GetRing() const { return ring; }

  void
  SetAzimuth(double azimuth) { driveAngles.azimuth = azimuth; }
  void
  SetElevation(double elevation) { driveAngles.elevation = elevation; }
  void
  SetHeliostatToEnuTransform(const Matrix3d& transform) { heliostatToEnuTransform = transform; }

  void ComputeTransforms(const Vector3d&);

  static double pedestalHeight;
  static double width;
  static double height;
  static double diagonal;
  static double reflectiveArea;
  static double area;

 private:
  vector<facet> facets;
  const Vector3d fieldCoords;
  const double aimOffset;
  const double focalLength;

  driveAngles driveAngles{1000, 1000};

  Matrix3d heliostatToEnuTransform;

 protected:
  heliostat(double E, double N, double U, double Z, double F, int nRows, int nCols, double fGap, int ring = 0);

  const int numRows;
  const int numCols;
  const double facetGap;
  const int ring;
};

class heliostat_115m2 : public heliostat {
 public:
  heliostat_115m2(double E, double N, double U, double Z, double F, int ring);
};
}  // namespace cspflux
