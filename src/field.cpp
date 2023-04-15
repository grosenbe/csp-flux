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

    heliostats.push_back(std::make_unique<heliostat>(stod(tokens[0]),
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
field::ComputeDriveAngles(const Vector3d &sun, size_t startIdx, size_t endIdx) {
  if (sun.norm() != 1) {
    throw std::runtime_error("field::ComputeDriveAngles: pass a unit sun vector");
  }
  if (startIdx < 0) {
    throw std::runtime_error("field::ComputeDriveAngles: start index less than zero");
  }
  if (endIdx >= heliostats.size()) {
    throw std::runtime_error("field::ComputeDriveAngles: end index greater than number of heliostats");
  }
  if (startIdx > endIdx) {
    throw std::runtime_error("field::ComputeDriveAngles: start index greater than end index");
  }

  for (size_t i = startIdx; i <= endIdx; ++i) {
    auto &helio = heliostats[i];
    auto e = helio->GetFieldCoords()[0];
    auto n = helio->GetFieldCoords()[1];
    auto fieldAz = std::atan2(n, e);

    // aim point
    Vector3d aimEnu = Vector3d(std::cos(fieldAz) * receiver.radius, std::sin(fieldAz) * receiver.radius, 0) + Vector3d(0, 0, tower::height + receiver::height * 0.5 + helio->GetZOffset());
    Vector3d heliostatAzDrive = helio->GetFieldCoords() + Vector3d(0, 0, helio->pedistalHeight);
    Vector3d heliostatToAimPoint = aimEnu - heliostatAzDrive;

    Vector3d heliostatNormal = (heliostatToAimPoint.normalized() + sun).normalized();

    double elAngle = std::atan2(heliostatNormal(2), std::sqrt(std::pow(heliostatNormal(0), 2) + std::pow(heliostatNormal(1), 2)));

    double azAngle = std::atan2(heliostatNormal(0), heliostatNormal(1));
    auto az = std::fmod(180 / PI * azAngle, 360.0);
    if (az < 0) az += 360;
    helio->SetAzimuth(az);
    helio->SetElevation(std::fmod(180 / PI * elAngle, 360.0));
  }
}
