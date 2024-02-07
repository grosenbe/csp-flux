#include "heliostat.h"

#include <stdexcept>

#include "field.h"
#include "utils.h"

using namespace cspflux;

double heliostat::pedestalHeight = 0;
double heliostat::width = 0;
double heliostat::height = 0;
double heliostat::diagonal = 0;
double heliostat::reflectiveArea = 0;

heliostat::heliostat(double E, double N, double U, double Z, double F, int numRows, int numCols, double facetGap, int ring)
    : fieldCoords(Vector3d(E, N, U)), aimOffset(Z), focalLength(F), numRows(numRows), numCols(numCols), facetGap(facetGap), ring(ring) {
  auto arrayHeight = GetNumRows() * facet::height + (GetNumRows() - 1) * facetGap;
  auto arrayWidth = GetNumCols() * facet::width + (GetNumCols() - 1) * facetGap;

  auto currentHeight = -1 * (arrayHeight / 2 - 0.5 * facet::height);
  for (auto row = 0; row < GetNumRows(); ++row) {
    auto currentWidth = -1 * (arrayWidth / 2 - 0.5 * facet::width);
    for (auto col = 0; col < GetNumCols(); ++col) {
      auto x = currentWidth;
      auto y = 0;
      auto z = currentHeight;
      facets.push_back(facet(Vector3d(x, y, z)));
      currentWidth += facet::width + facetGap;
    }
    currentHeight += facet::height + facetGap;
  }
}

heliostat_115m2::heliostat_115m2(double E, double N, double U, double Z, double F, int ring)
    : heliostat(E, N, U, Z, F, 5, 7, 0.0254, ring) {
  heliostat::pedestalHeight = 10;
  heliostat::width = facet::width * numCols;
  heliostat::height = facet::height * numRows;
  heliostat::diagonal = std::sqrt(std::pow(heliostat::height, 2) + std::pow(heliostat::width, 2));
  heliostat::reflectiveArea = heliostat::height * heliostat::width;
}

const Matrix3d&
heliostat::GetHeliostatToEnuTransform() const {
  if (GetDriveAngles().azimuth == 1000 && GetDriveAngles().elevation == 1000) {
    throw std::runtime_error("Cannot return heliostat to ENU transform before calculating drive angles");
  }

  return heliostatToEnuTransform;
}

void
heliostat::ComputeTransforms(const Vector3d& sun) {
  auto e = GetFieldCoords()[0];
  auto n = GetFieldCoords()[1];
  auto fieldAz = std::atan2(n, e);

  auto aimEnu = Vector3d(std::cos(fieldAz) * receiver::radius, std::sin(fieldAz) * receiver::radius, 0) + Vector3d(0, 0, tower::height + receiver::height * 0.5 + GetAimOffset());
  auto heliostatAzDrive = GetFieldCoords() + Vector3d(0, 0, pedestalHeight);
  auto heliostatToAimPoint = aimEnu - heliostatAzDrive;

  auto heliostatNormal = (heliostatToAimPoint.normalized() + sun).normalized();

  auto elAngle = std::atan2(heliostatNormal(2), std::sqrt(std::pow(heliostatNormal(0), 2) + std::pow(heliostatNormal(1), 2)));

  auto azAngle = std::atan2(heliostatNormal(0), heliostatNormal(1));
  auto az = std::fmod(R2D * azAngle, 360.0);
  if (az < 0) az += 360;
  SetAzimuth(az);
  SetElevation(std::fmod(R2D * elAngle, 360.0));

  auto azRot = RotationAboutVector(Vector3d(0, 0, 1), GetDriveAngles().azimuth * D2R);
  auto rotatedElAxis = azRot * Vector3d(1, 0, 0);
  auto elRot = RotationAboutVector(rotatedElAxis, -GetDriveAngles().elevation * D2R);
  SetHeliostatToEnuTransform(elRot * azRot);

  for (auto& facet : facets) {
    auto transform = GetHeliostatToEnuTransform();
    auto facetCenterEnu = transform * facet.GetCenterHel() + heliostatAzDrive;

    auto facetNormalHel = (2 * focalLength * Vector3d(0, 1, 0) - facet.GetCenterHel()).normalized();
    auto facetWidthHel = Vector3d(1, 0, 0);
    auto facetHeightHel = facetWidthHel.cross(facetNormalHel).normalized();

    facet.SetBasisVecs(facetCenterEnu, transform * facetWidthHel, transform * facetHeightHel, transform * facetNormalHel);
  }
}
