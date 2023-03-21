#include <gtest/gtest.h>

#include "src/field.h"
#include "src/utils.h"

using namespace cspflux;

TEST(utilstests, CompareDoubles) {
  EXPECT_TRUE(CompareDoubles(1, 1));
  EXPECT_TRUE(CompareDoubles(1.05, 1.05));
  EXPECT_TRUE(CompareDoubles(-1, -1));
  EXPECT_TRUE(CompareDoubles(-1.5, -1.5));
  EXPECT_FALSE(CompareDoubles(1, 1 + 0.000005));
  EXPECT_FALSE(CompareDoubles(1, -1));
  EXPECT_FALSE(CompareDoubles(1, 2));
}

TEST(heliostattests, field) {
  EXPECT_ANY_THROW(field("does/not/exist"));

  field f("test/testfield.txt");

  EXPECT_EQ(f.GetSize(), 9332);

  auto h1 = f.GetHeliostat(0);
  auto h2 = f.GetHeliostat(f.GetSize() - 1);

  EXPECT_EQ(h1.GetFieldCoords()[0], 11.72784939);
  EXPECT_EQ(h1.GetFieldCoords()[1], 129.6183538);
  EXPECT_EQ(h1.GetFieldCoords()[2], 0);

  EXPECT_EQ(h2.GetFieldCoords()[0], -23.69186385);
  EXPECT_EQ(h2.GetFieldCoords()[1], 1527.036711);
  EXPECT_EQ(h2.GetFieldCoords()[2], 0);
}
