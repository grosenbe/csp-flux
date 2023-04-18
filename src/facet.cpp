#include "facet.h"

#include "utils.h"

double facet::width = 1.605;
double facet::height = 2.06;

facet::facet(const Vector3d &centerHel) : centerHel(centerHel) {
}

void
facet::SetBasisVecs(const Vector3d &enu, const Vector3d &width, const Vector3d &height, const Vector3d &normal) {
  assert(cspflux::CompareDoubles(width.norm(), 1));
  assert(cspflux::CompareDoubles(height.norm(), 1));
  assert(cspflux::CompareDoubles(normal.norm(), 1));

  centerEnu = enu;
  normalBasisEnu = normal;
  widthBasisEnu = width;
  heightBasisEnu = height;
  isFullyInitialized = true;
}

const Vector3d &
facet::GetNormalBasisEnu() const {
  if (!isFullyInitialized) {
    throw std::runtime_error("Tried to get basis before facets are initialized");
  }

  return normalBasisEnu;
}

const Vector3d &
facet::GetWidthBasisEnu() const {
  if (!isFullyInitialized) {
    throw std::runtime_error("Tried to get basis before facets are initialized");
  }

  return widthBasisEnu;
}

const Vector3d &
facet::GetHeightBasisEnu() const {
  if (!isFullyInitialized) {
    throw std::runtime_error("Tried to get basis before facets are initialized");
  }
  return heightBasisEnu;
}
