#include <gtest/gtest.h>

#include <cmath>
#include <eigen3/Eigen/Dense>

#include "src/field.h"
#include "src/parameters.h"
#include "src/sunPointGenerator.h"
#include "src/utils.h"

using namespace cspflux;

int receiver::Num_Panels = 14;
double receiver::height = 40;
double receiver::radius = 12;
double tower::height = 140;
double SimulationParams::sigAz = 0;
double SimulationParams::sigEl = 0;

TEST(utilstests, CompareDoubles) {
  EXPECT_TRUE(CompareDoubles(1, 1));
  EXPECT_TRUE(CompareDoubles(1.05, 1.05));
  EXPECT_TRUE(CompareDoubles(-1, -1));
  EXPECT_TRUE(CompareDoubles(-1.5, -1.5));
  EXPECT_FALSE(CompareDoubles(1, 1 + 0.000005));
  EXPECT_FALSE(CompareDoubles(1, -1));
  EXPECT_FALSE(CompareDoubles(1, 2));
}

TEST(utilstests, SunPoints) {
  Vector3d sunCenter(0, 0, 1);
  auto generator = sunPointGenerator(sunCenter);

  auto sunPoints = generator.GenerateSunPoints(1000000);

  double maxAngle = 0;
  double minAngle = std::numeric_limits<double>::min();
  for (const auto &p : sunPoints) {
    auto angle = std::acos(p.dot(sunCenter));
    if (angle > maxAngle)
      maxAngle = angle;
    if (angle < minAngle)
      minAngle = angle;
  }
  EXPECT_TRUE(CompareDoubles(maxAngle, 0.00465));
  EXPECT_TRUE(CompareDoubles(minAngle, 0));
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
  EXPECT_EQ(h1.GetZOffset(), -1);

  EXPECT_EQ(h2.GetFieldCoords()[0], -23.69186385);
  EXPECT_EQ(h2.GetFieldCoords()[1], 1527.036711);
  EXPECT_EQ(h2.GetFieldCoords()[2], 0);
  EXPECT_EQ(h2.GetZOffset(), 0);

  EXPECT_ANY_THROW(f.ComputeNominalDriveAngles(Vector3d(0, 0, 1), -1, 0));
  EXPECT_ANY_THROW(f.ComputeNominalDriveAngles(Vector3d(0, 0, 1), 2, 1));
  EXPECT_ANY_THROW(f.ComputeNominalDriveAngles(Vector3d(0, 0, 1), 0, 9332));
  EXPECT_ANY_THROW(f.ComputeNominalDriveAngles(Vector3d(0, 1, 1), 0, 9332));

  f.ComputeNominalDriveAngles(Vector3d(0, 0, 1), 0, 9331);
  for (auto i = 0u; i < fieldSize; ++i) {
    EXPECT_TRUE(f.GetHeliostat(i).driveAngles.azimuth >= 0 && f.GetHeliostat(i).driveAngles.azimuth <= 360);
    EXPECT_TRUE(f.GetHeliostat(i).driveAngles.elevation >= -180 && f.GetHeliostat(i).driveAngles.elevation <= 180);
  }
}
