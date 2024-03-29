#pragma once

#include <eigen3/Eigen/Dense>
#include <memory>
#include <string>
#include <vector>

#include "heliostat.h"

using Eigen::Vector3d;
using std::unique_ptr;
using std::vector;

namespace cspflux {

struct tower {
  static double height;
};

struct receiver {
  static double height;
  static double radius;

  static int Num_Panels;
};

class field {
 public:
  field(const std::string&);

  size_t
  GetSize() { return heliostats.size(); }

  heliostat& GetHeliostat(size_t);
  void ComputeHeliostatAndFacetTransforms(const Vector3d&, size_t, size_t);

  tower tower;
  receiver receiver;

 private:
  vector<unique_ptr<heliostat>> heliostats;
};
}  // namespace cspflux
