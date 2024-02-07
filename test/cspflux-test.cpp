#include <gtest/gtest.h>

#include <cmath>
#include <eigen3/Eigen/Dense>

#include "spa/spa.h"
#include "src/field.h"
#include "src/limbDarkenedSunPointGenerator.h"
#include "src/parameters.h"
#include "src/pointSunPointGenerator.h"
#include "src/utils.h"

using namespace cspflux;

using namespace Eigen;

int receiver::Num_Panels = 14;
double receiver::height = 40;
double receiver::radius = 12;
double tower::height = 140;

double simulationParams::sigAz = 0;
double simulationParams::sigEl = 0;
int simulationParams::year = 2023;
int simulationParams::month = 4;
int simulationParams::day = 13;
int simulationParams::hour = 15;
int simulationParams::minute = 17;
double simulationParams::second = 0;
double simulationParams::timezone = -8;
double simulationParams::longitude = -122.2321396;
double simulationParams::latitude = 47.7326959;
double simulationParams::elevation = 152;
double simulationParams::temperature = 11;
double simulationParams::pressure = 1000;

namespace {
void
CompareVectors(const Vector3d &v1, const Vector3d &v2) {
  EXPECT_TRUE(CompareDoubles(v1(0), v2(0)));
  EXPECT_TRUE(CompareDoubles(v1(1), v2(1)));
  EXPECT_TRUE(CompareDoubles(v1(2), v2(2)));
}
}  // namespace

TEST(utilstests, CompareDoubles) {
  EXPECT_TRUE(CompareDoubles(1, 1));
  EXPECT_TRUE(CompareDoubles(1.05, 1.05));
  EXPECT_TRUE(CompareDoubles(-1, -1));
  EXPECT_TRUE(CompareDoubles(-1.5, -1.5));
  EXPECT_FALSE(CompareDoubles(1, 1 + 0.000005));
  EXPECT_FALSE(CompareDoubles(1, -1));
  EXPECT_FALSE(CompareDoubles(1, 2));
}

TEST(sunpointgeneratortests, limbdarkened_between_0_and_465) {
  Vector3d sunCenter(0, 0, 1);
  auto generator = limbDarkenedSunPointGenerator(sunCenter);

  double maxAngle = 0;
  double minAngle = std::numeric_limits<double>::max();
  auto numPoints = 0u;
  while (numPoints++ < 10000) {
    auto p = generator.GenerateSunPoint();
    auto angle = std::acos(p.dot(sunCenter));
    if (angle > maxAngle)
      maxAngle = angle;
    if (angle < minAngle)
      minAngle = angle;
  }
  EXPECT_GT(maxAngle, 0.0045);
  EXPECT_LT(minAngle, 0.00005);
}

TEST(sunpointgeneratortests, pointSun) {
  Vector3d sunCenter(0, 0, 1);
  auto generator = pointSunPointGenerator(sunCenter);

  auto sunPoint = generator.GenerateSunPoint();
  EXPECT_EQ(sunPoint, sunCenter);
}

TEST(heliostattests, field) {
  EXPECT_ANY_THROW(field("does/not/exist"));

  field f("test/testfield.txt");
  auto fieldSize = f.GetSize();
  EXPECT_EQ(fieldSize, 9332);

  auto h1 = f.GetHeliostat(0);
  auto h2 = f.GetHeliostat(f.GetSize() - 1);

  EXPECT_EQ(h1.GetFieldCoords()[0], 11.72784939);
  EXPECT_EQ(h1.GetFieldCoords()[1], 129.6183538);
  EXPECT_EQ(h1.GetFieldCoords()[2], 0);
  EXPECT_EQ(h1.GetAimOffset(), -1);
  EXPECT_EQ(h1.GetFocalLength(), -1);
  EXPECT_EQ(h1.GetRing(), 1);
  EXPECT_ANY_THROW(h1.GetHeliostatToEnuTransform());
  EXPECT_EQ(h2.GetRing(), 73);

  const auto facets = h1.GetFacets();
  auto bottomLeftIdx = 0;
  auto bottomRightIdx = h1.GetNumCols() - 1;
  auto topLeftIdx = h1.GetNumCols() * (h1.GetNumRows() - 1);
  auto topRightIdx = h1.GetNumCols() * h1.GetNumRows() - 1;
  EXPECT_TRUE(CompareDoubles(facets[bottomLeftIdx].GetCenterHel()(0), facets[topLeftIdx].GetCenterHel()(0)));
  EXPECT_TRUE(CompareDoubles(facets[bottomRightIdx].GetCenterHel()(0), facets[topRightIdx].GetCenterHel()(0)));
  EXPECT_TRUE(CompareDoubles(facets[topLeftIdx].GetCenterHel()(2), facets[topRightIdx].GetCenterHel()(2)));
  EXPECT_TRUE(CompareDoubles(facets[bottomRightIdx].GetCenterHel()(2), facets[bottomLeftIdx].GetCenterHel()(2)));
  EXPECT_TRUE(CompareDoubles(facets[bottomLeftIdx].GetCenterHel()(2), -facets[topLeftIdx].GetCenterHel()(2)));
  EXPECT_TRUE(CompareDoubles(facets[topLeftIdx].GetCenterHel()(0), -facets[topRightIdx].GetCenterHel()(0)));

  EXPECT_EQ(h2.GetFieldCoords()[0], -23.69186385);
  EXPECT_EQ(h2.GetFieldCoords()[1], 1527.036711);
  EXPECT_EQ(h2.GetFieldCoords()[2], 0);
  EXPECT_EQ(h2.GetAimOffset(), 0);
  EXPECT_EQ(h2.GetFocalLength(), -1);
  EXPECT_ANY_THROW(h2.GetHeliostatToEnuTransform());

  EXPECT_ANY_THROW(f.ComputeHeliostatAndFacetTransforms(Vector3d(0, 0, 1), -1, 0));
  EXPECT_ANY_THROW(f.ComputeHeliostatAndFacetTransforms(Vector3d(0, 0, 1), 2, 1));
  EXPECT_ANY_THROW(f.ComputeHeliostatAndFacetTransforms(Vector3d(0, 0, 1), 0, 9332));
  EXPECT_ANY_THROW(f.ComputeHeliostatAndFacetTransforms(Vector3d(0, 1, 1), 0, 9332));

  f.ComputeHeliostatAndFacetTransforms(Vector3d(0, 0, 1), 0, f.GetSize() - 1);
  for (auto i = 0u; i < fieldSize; ++i) {
    EXPECT_TRUE(f.GetHeliostat(i).GetDriveAngles().azimuth >= 0);
    EXPECT_TRUE(f.GetHeliostat(i).GetDriveAngles().azimuth <= 360);
    EXPECT_TRUE(f.GetHeliostat(i).GetDriveAngles().elevation >= -180);
    EXPECT_TRUE(f.GetHeliostat(i).GetDriveAngles().elevation <= 180);
    f.GetHeliostat(i).GetHeliostatToEnuTransform();
  }
}

TEST(heliostattests, creates_transforms) {
  field f("test/testfield.txt");
  auto helio = f.GetHeliostat(1);

  helio.ComputeTransforms(Vector3d(0, 0, 1));
  EXPECT_GT(helio.GetDriveAngles().elevation, 89.809);
  EXPECT_TRUE(CompareDoubles(helio.GetDriveAngles().azimuth, 180));
}

TEST(heliostattests, heliostat_creates_facets) {
  heliostat_115m2 h(0, 0, 0, 0, -1, 0);

  EXPECT_EQ(h.GetFacets().size(), 35);
}

TEST(heliostattests, facet_sets_center_on_construction) {
  Vector3d center(0, 0, 0);
  auto f = facet(center);

  EXPECT_ANY_THROW(f.GetNormalBasisEnu());
  EXPECT_ANY_THROW(f.GetWidthBasisEnu());
  EXPECT_ANY_THROW(f.GetHeightBasisEnu());

  f.SetBasisVecs(Vector3d(0, 0, 0), Vector3d(1, 0, 0), Vector3d(0, 1, 0), Vector3d(0, 0, 1));
  f.GetNormalBasisEnu();
  f.GetWidthBasisEnu();
  f.GetHeightBasisEnu();
}

TEST(utilstests, runSPA) {
  field f("test/testfield.txt");
  auto spaData = CreateSpaData();

  EXPECT_EQ(spa_calculate(&spaData), 0);

  spa_data sd;
  sd.zenith = 0;
  sd.azimuth = 0;

  CompareVectors(ConvertSpaDataToEnu(sd), Vector3d(0, 0, 1));
}

TEST(utilstests, rotation) {
  for (int i = 0; i < 15; ++i) {
    auto angle = i / 15.0 * 2 * PI;

    Matrix3d xRotMtx, yRotMtx, zRotMtx;

    xRotMtx << 1, 0, 0,
        0, std::cos(angle), std::sin(angle),
        0, -std::sin(angle), std::cos(angle);

    yRotMtx << std::cos(angle), 0, -std::sin(angle),
        0, 1, 0,
        std::sin(angle), 0, std::cos(angle);

    zRotMtx << std::cos(angle), std::sin(angle), 0,
        -std::sin(angle), std::cos(angle), 0,
        0, 0, 1;

    EXPECT_TRUE(RotationAboutVector(Vector3d(1, 0, 0), angle).isApprox(xRotMtx));
    EXPECT_TRUE(RotationAboutVector(Vector3d(0, 1, 0), angle).isApprox(yRotMtx));
    EXPECT_TRUE(RotationAboutVector(Vector3d(0, 0, 1), angle).isApprox(zRotMtx));
  }
}
