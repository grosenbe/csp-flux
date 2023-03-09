#include "utils.h"

#include <algorithm>
using namespace cspflux;

bool cspflux::CompareDoubles(double a, double b) {
  auto eps = 0.00001;
  if (std::abs(a - b) > eps)
    return false;
  return true;
}
