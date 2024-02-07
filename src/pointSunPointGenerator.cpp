#include "pointSunPointGenerator.h"

#include "utils.h"

using namespace cspflux;

pointSunPointGenerator::pointSunPointGenerator(const Vector3d &sunCenter) : sunPointGenerator(sunCenter) {
}

Vector3d
pointSunPointGenerator::GenerateSunPoint() {
  return sunCenter;
}
