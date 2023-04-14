#include "utils.h"

#include <algorithm>

#include "parameters.h"

using Eigen::Vector3d;

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
