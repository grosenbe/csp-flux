#include "heliostat.h"

using namespace cspflux;

double heliostat::pedistalHeight = 10;

heliostat::heliostat(double E, double N, double U, double Z, double F)
  : fieldCoords(Vector3d(E, N, U)), zOffset(Z), focalLength(F) {}

heliostat::heliostat(const heliostat &other) : fieldCoords(other.fieldCoords), zOffset(other.zOffset), focalLength(other.focalLength) {
  driveAngles.azimuth = other.driveAngles.azimuth;
  driveAngles.elevation = other.driveAngles.elevation;
}
