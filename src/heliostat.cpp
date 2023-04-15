#include "heliostat.h"

using namespace cspflux;

double heliostat::pedistalHeight = 10;

heliostat::heliostat(double E, double N, double U, double Z, double F, int numRows, int numCols, double facetGap)
    : fieldCoords(Vector3d(E, N, U)), zOffset(Z), focalLength(F), numRows(numRows), numCols(numCols), facetGap(facetGap) {}

heliostat_SR115::heliostat_SR115(double E, double N, double U, double Z, double F)
    : heliostat(E, N, U, Z, F, 7, 5, 0.0254) {}
