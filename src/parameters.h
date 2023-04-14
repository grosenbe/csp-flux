#pragma once

namespace cspflux {
struct simulationParams {
  static double sigAz;
  static double sigEl;

  // SPA parameters
  static int year;
  static int month;
  static int day;
  static int hour;
  static int minute;
  static double second;

  static double timezone;
  static double longitude;    // [deg] (+ve east)
  static double latitude;     // [deg]
  static double elevation;    // [m]
  static double temperature;  // [c]
  static double pressure;     // [mbar]
};
}  // namespace cspflux
