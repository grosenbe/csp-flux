#include "heliostat.h"

#include <stdexcept>

using namespace cspflux;

double heliostat::pedistalHeight = 10;

heliostat::heliostat(double E, double N, double U, double Z, double F, int numRows, int numCols, double facetGap)
    : fieldCoords(Vector3d(E, N, U)), aimOffset(Z), focalLength(F), numRows(numRows), numCols(numCols), facetGap(facetGap) {}

heliostat_SR115::heliostat_SR115(double E, double N, double U, double Z, double F)
    : heliostat(E, N, U, Z, F, 5, 7, 0.0254) {}

const Matrix3d&
heliostat::GetHeliostatToEnuTransform() {
  if (GetDriveAngles().azimuth == 1000 && GetDriveAngles().elevation == 1000) {
    throw std::runtime_error("Cannot return heliostat to ENU transform before calculating drive angles");
  }

  return heliostatToEnuTransform;
}
