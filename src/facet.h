#pragma once

#include <eigen3/Eigen/Dense>

using namespace Eigen;

class facet {
 public:
  facet() = delete;
  facet(const Vector3d&);

  const Vector3d&
  GetNormalBasisEnu() const;
  const Vector3d&
  GetWidthBasisEnu() const;
  const Vector3d&
  GetHeightBasisEnu() const;

  void
  SetBasisVecs(const Vector3d&, const Vector3d&, const Vector3d&, const Vector3d&);

  const Vector3d&
  GetCenterHel() const { return centerHel; }
  const Vector3d&
  GetCenterEnu() const { return centerEnu; }

  static double width;
  static double height;

 private:
  bool isFullyInitialized = false;

  Vector3d centerHel;
  Vector3d centerEnu;

  Vector3d normalBasisEnu;
  Vector3d widthBasisEnu;
  Vector3d heightBasisEnu;
};
