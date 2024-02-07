#include "sunPointGenerator.h"

#include <eigen3/Eigen/Dense>
#include <vector>

using std::vector;

using namespace cspflux;

sunPointGenerator::sunPointGenerator(const Vector3d &sunCenter)
    : sunCenter(sunCenter) {
  slntRgax = 1 - std::cos(0.00465);

  sunCoordinateBasis = vector<Vector3d>(3);
  sunCoordinateBasis[0] = sunCenter;
  sunCoordinateBasis[1] = Vector3d(1, 0, 0);
  if (sunCoordinateBasis[0](0) != 0 || sunCoordinateBasis[0](1) != 0) {
    sunCoordinateBasis[1](0) = -sunCoordinateBasis[0](1);
    sunCoordinateBasis[1](1) = sunCoordinateBasis[0](0);
  }
  sunCoordinateBasis[1].normalize();
  sunCoordinateBasis[2] = sunCoordinateBasis[0].cross(sunCoordinateBasis[1]);
  sunCoordinateBasis[2].normalize();
}
