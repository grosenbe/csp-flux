#include "limbDarkenedSunPointGenerator.h"

#include "utils.h"

using namespace cspflux;

limbDarkenedSunPointGenerator::limbDarkenedSunPointGenerator(const Vector3d &sunCenter, int seed) : sunPointGenerator(sunCenter) {
  engine.seed(seed);
}

vector<Vector3d>
limbDarkenedSunPointGenerator::GenerateSunPoints(int numPointsToGenerate) {
  int numPoints = 0;

  vector<Vector3d> sunPoints(numPointsToGenerate);

  while (numPoints < numPointsToGenerate) {
    auto v1 = 1 - slntRgax * distribution(engine);
    auto asd = std::acos(v1);

    auto density = 1 - 1 > asd / 0.00465 ? asd / 0.00465 : 1;

    auto d1 = distribution(engine);

    if (d1 > density) continue;

    auto v0 = distribution(engine);

    auto rk = std::sqrt(1 - v1 * v1);
    auto v2 = std::cos(v0 * 2 * PI);
    auto v3 = std::sin(v0 * 2 * PI);
    auto V_ENU = Vector3d(v1, rk * v2, rk * v3).normalized();

    sunPoints[numPoints++] = (V_ENU(0) * sunCoordinateBasis[0] + V_ENU(1) * sunCoordinateBasis[1] + V_ENU(2) * sunCoordinateBasis[2]).normalized();
  }
  return sunPoints;
}
