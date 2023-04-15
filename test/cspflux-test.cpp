#include <gtest/gtest.h>

#include <cmath>
#include <eigen3/Eigen/Dense>

#include "spa/spa.h"
#include "src/field.h"
#include "src/limbDarkenedSunPointGenerator.h"
#include "src/parameters.h"
#include "src/utils.h"

using namespace cspflux;

using Eigen::Vector3d;

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
VerifyENUVector(const Vector3d &v1, const Vector3d &v2) {
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

TEST(sunpointgeneratortests, limbdarkened) {
  Vector3d sunCenter(0, 0, 1);
  auto generator = limbDarkenedSunPointGenerator(sunCenter);

  auto sunPoints = generator.GenerateSunPoints(100000);

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
  EXPECT_EQ(h1.GetFocalLength(), -1);

  EXPECT_EQ(h2.GetFieldCoords()[0], -23.69186385);
  EXPECT_EQ(h2.GetFieldCoords()[1], 1527.036711);
  EXPECT_EQ(h2.GetFieldCoords()[2], 0);
  EXPECT_EQ(h2.GetZOffset(), 0);
  EXPECT_EQ(h2.GetFocalLength(), -1);

  EXPECT_ANY_THROW(f.ComputeDriveAngles(Vector3d(0, 0, 1), -1, 0));
  EXPECT_ANY_THROW(f.ComputeDriveAngles(Vector3d(0, 0, 1), 2, 1));
  EXPECT_ANY_THROW(f.ComputeDriveAngles(Vector3d(0, 0, 1), 0, 9332));
  EXPECT_ANY_THROW(f.ComputeDriveAngles(Vector3d(0, 1, 1), 0, 9332));

  f.ComputeDriveAngles(Vector3d(0, 0, 1), 0, 9331);
  for (auto i = 0u; i < fieldSize; ++i) {
    EXPECT_TRUE(f.GetHeliostat(i).GetDriveAngles().azimuth >= 0);
    EXPECT_TRUE(f.GetHeliostat(i).GetDriveAngles().azimuth <= 360);
    EXPECT_TRUE(f.GetHeliostat(i).GetDriveAngles().elevation >= -180);
    EXPECT_TRUE(f.GetHeliostat(i).GetDriveAngles().elevation <= 180);
  }
}

TEST(utilstests, runSPA) {
  field f("test/testfield.txt");
  auto spaData = CreateSpaData();

  EXPECT_EQ(spa_calculate(&spaData), 0);

  spa_data sd;
  sd.zenith = 0;
  sd.azimuth = 0;

  VerifyENUVector(ConvertSpaDataToEnu(sd), Vector3d(0, 0, 1));
}
