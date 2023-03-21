#pragma once

#include <memory>
#include <string>
#include <vector>

#include "heliostat.h"

using std::unique_ptr;
using std::vector;

namespace cspflux {
class field {
 public:
  field(const std::string&);

  size_t
  GetSize() { return heliostats.size(); }

  heliostat& GetHeliostat(size_t);

 private:
  vector<unique_ptr<heliostat>> heliostats;
};
}  // namespace cspflux
