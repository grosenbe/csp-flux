#include "heliostat.h"

using namespace cspflux;

double heliostat::pedistalHeight = 10;

heliostat::heliostat(double E, double N, double U, double Z)
    : fieldCoords(std::array<double, 3>{E, N, U}), zOffset(Z) {}

heliostat::heliostat(const heliostat &other) : fieldCoords(other.fieldCoords), zOffset(other.zOffset) {
  driveAngles.azimuth = other.driveAngles.azimuth;
  driveAngles.elevation = other.driveAngles.elevation;
}
