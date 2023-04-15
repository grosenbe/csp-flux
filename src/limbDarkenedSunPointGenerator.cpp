#include "limbDarkenedSunPointGenerator.h"

#include "utils.h"

using namespace cspflux;

limbDarkenedSunPointGenerator::limbDarkenedSunPointGenerator(const Vector3d &sunCenter, int seed) : sunPointGenerator(sunCenter) {
  engine.seed(seed);
}

Vector3d
limbDarkenedSunPointGenerator::GenerateSunPoint() {
  auto v1 = 1 - slntRgax * distribution(engine);

  auto v0 = distribution(engine);

  auto rk = std::sqrt(1 - v1 * v1);
  auto v2 = std::cos(v0 * 2 * PI);
  auto v3 = std::sin(v0 * 2 * PI);
  auto V_ENU = Vector3d(v1, rk * v2, rk * v3).normalized();

  return (V_ENU(0) * sunCoordinateBasis[0] + V_ENU(1) * sunCoordinateBasis[1] + V_ENU(2) * sunCoordinateBasis[2]).normalized();
}
