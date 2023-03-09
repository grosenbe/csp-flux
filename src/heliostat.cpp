#include "heliostat.h"

heliostat::heliostat(double E, double N, double U)
    : fieldCoords(std::array<double, 3>{E, N, U}) {}
