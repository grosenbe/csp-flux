#include "utils.h"

#include <algorithm>

#include "parameters.h"

using namespace Eigen;

bool
cspflux::CompareDoubles(double a, double b) {
  auto eps = 0.000001;
  if (std::abs(a - b) > eps)
    return false;
  return true;
}

spa_data
cspflux::CreateSpaData() {
  spa_data data;
  data.year = simulationParams::year;
  data.month = simulationParams::month;
  data.day = simulationParams::day;
  data.hour = simulationParams::hour;
  data.minute = simulationParams::minute;
  data.second = simulationParams::second;
  data.delta_ut1 = 0;
  data.delta_t = 0;
  data.timezone = simulationParams::timezone;
  data.longitude = simulationParams::longitude;
  data.latitude = simulationParams::latitude;
  data.elevation = simulationParams::elevation;
  data.pressure = simulationParams::pressure;
  data.temperature = simulationParams::temperature;
  data.slope = 0;
  data.azm_rotation = 0;
  data.atmos_refract = 0.5667;
  data.function = SPA_ZA;
  return data;
}

Vector3d
cspflux::ConvertSpaDataToEnu(const spa_data &spaData) {
  double ele = deg2rad(90 - spaData.zenith);
  double azm = deg2rad(spaData.azimuth);
  return Vector3d(std::cos(ele) * std::sin(azm), std::cos(ele) * std::cos(azm), std::sin(ele));
}

Matrix3d
cspflux::RotateAboutVector(const Vector3d &vec, double angle) {
  if (!CompareDoubles(vec.norm(), 1))
    throw std::runtime_error("Trying to rotate about an unnormalized vector");

  auto q0 = std::cos(angle / 2);
  auto q1 = std::sin(angle / 2) * vec(0);
  auto q2 = std::sin(angle / 2) * vec(1);
  auto q3 = std::sin(angle / 2) * vec(2);

  Matrix3d m;
  m(0, 0) = q1 * q1 - q2 * q2 - q3 * q3 + q0 * q0;
  m(0, 1) = 2 * (q1 * q2 + q3 * q0);
  m(0, 2) = 2 * (q1 * q3 - q2 * q0);

  m(1, 0) = 2 * (q1 * q2 - q3 * q0);
  m(1, 1) = -q1 * q1 + q2 * q2 - q3 * q3 + q0 * q0;
  m(1, 2) = 2 * (q2 * q3 + q1 * q0);

  m(2, 0) = 2 * (q1 * q3 + q2 * q0);
  m(2, 1) = 2 * (q2 * q3 - q1 * q0);
  m(2, 2) = -q1 * q1 - q2 * q2 + q3 * q3 + q0 * q0;
  return m;
}
