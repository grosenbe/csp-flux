#pragma once

#include <random>

#include "sunPointGenerator.h"

using std::vector;

namespace cspflux {
class pointSunPointGenerator : public sunPointGenerator {
 public:
  pointSunPointGenerator(const Vector3d &sunCenter);

  Vector3d GenerateSunPoint() override;
};
}  // namespace cspflux
