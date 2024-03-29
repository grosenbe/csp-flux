#pragma once

#include <random>

#include "sunPointGenerator.h"

using std::vector;

namespace cspflux {
class limbDarkenedSunPointGenerator : public sunPointGenerator {
 public:
  limbDarkenedSunPointGenerator(const Vector3d &sunCenter, int seed = 0);

  Vector3d GenerateSunPoint() override;

 private:
  std::uniform_real_distribution<> distribution;
  std::default_random_engine engine;
};
}  // namespace cspflux
