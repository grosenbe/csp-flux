#include "utils.h"

#include <algorithm>
#include <memory>
#include <stdexcept>

using namespace cspflux;

bool
cspflux::CompareDoubles(double a, double b) {
  auto eps = 0.000001;
  if (std::abs(a - b) > eps)
    return false;
  return true;
}
