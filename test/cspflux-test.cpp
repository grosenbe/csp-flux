#include <gtest/gtest.h>

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
