#include "field.h"

#include <array>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <fstream>
#include <sstream>
#include <string>

#include "heliostat.h"
#include "parameters.h"
#include "utils.h"

using Eigen::Vector3d;
using std::ifstream;
using std::string;
using std::stringstream;

using namespace cspflux;

field::field(const std::string &path) {
  ifstream ifs(path, std::ifstream::in);
  if (!ifs.good())
    throw std::runtime_error("Error: unable to open input file at " + path);

  std::string line;
  while (std::getline(ifs, line)) {
    if (line[0] == '#') continue;

    stringstream ss(line);
    std::array<string, 5> tokens;
    for (auto index = 0u; index < 5; ++index) {
      std::getline(ss, tokens[index], '\t');
    }

    heliostats.push_back(std::make_unique<heliostat_115m2>(stod(tokens[0]),
                                                           stod(tokens[1]),
                                                           stod(tokens[2]),
                                                           stod(tokens[3]),
                                                           stod(tokens[4])));
  }
}

heliostat &
field::GetHeliostat(size_t heliostatIdx) {
  return *(heliostats[heliostatIdx]);
}

void
field::ComputeHeliostatAndFacetTransforms(const Vector3d &sun, size_t startIdx, size_t endIdx) {
  if (sun.norm() != 1)
    throw std::runtime_error("field::ComputeDriveAngles: pass a unit sun vector");

  if (startIdx < 0)
    throw std::runtime_error("field::ComputeDriveAngles: start index less than zero");

  if (endIdx >= heliostats.size())
    throw std::runtime_error("field::ComputeDriveAngles: end index greater than number of heliostats");

  if (startIdx > endIdx)
    throw std::runtime_error("field::ComputeDriveAngles: start index greater than end index");

  for (size_t i = startIdx; i <= endIdx; ++i) {
    heliostats[i]->ComputeTransforms(sun);
  }
}
