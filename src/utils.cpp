#include "utils.h"

#include <algorithm>
using namespace cspflux;

bool cspflux::CompareDoubles(double a, double b) {
  auto eps = 0.000001;
  if (std::abs(a - b) > eps)
    return false;
  return true;
}

const double &Matrix::operator()(int r, int c) const { return data[r][c]; }
double &Matrix::operator()(int r, int c) { return data[r][c]; }

bool Matrix::operator==(const Matrix &other) const {
  for (auto r = 0u; r < 3; ++r)
    for (auto c = 0u; c < 3; c++)
      if (!CompareDoubles(data[r][c], other.data[r][c]))
        return false;
  return true;
}

Matrix Matrix::Transpose() {
  Matrix transposed;
  transposed(0, 0) = data[0][0];
  transposed(1, 0) = data[0][1];
  transposed(2, 0) = data[0][2];

  transposed(0, 1) = data[1][0];
  transposed(1, 1) = data[1][1];
  transposed(2, 1) = data[1][2];

  transposed(0, 2) = data[2][0];
  transposed(1, 2) = data[2][1];
  transposed(2, 2) = data[2][2];

  return transposed;
}

double Matrix::Determinant() {
  return data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2]) -
         data[0][1] * (data[1][0] * data[2][2] - data[2][0] * data[1][2]) +
         data[0][2] * (data[1][0] * data[2][1] - data[2][0] * data[1][1]);
}
