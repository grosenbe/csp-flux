#include "src/utils.h"

#include <gtest/gtest.h>

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

TEST(utilstests, MatrixComparison) {
  Matrix m1({{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}});
  Matrix m2({{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}});
  Matrix m3({{{1, 2, 3}, {4, 5, 6}, {7, 8, 3.14}}});
  Matrix m5({{{1, 4, 7}, {2, 5, 8}, {3, 6, 9}}});

  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
  EXPECT_TRUE(m1.Transpose() == m5);

  EXPECT_TRUE(m1.Determinant() == 0.);
}
