#include "utils.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

using std::vector;
using namespace cspflux;

bool
cspflux::CompareDoubles(double a, double b) {
  auto eps = 0.000001;
  if (std::abs(a - b) > eps)
    return false;
  return true;
}

const double &
Matrix::operator()(int r, int c) const { return data[r][c]; }
double &
Matrix::operator()(int r, int c) { return data[r][c]; }

bool
Matrix::operator==(const Matrix &other) const {
  for (auto r = 0u; r < 3; ++r)
    for (auto c = 0u; c < 3; c++)
      if (!CompareDoubles(data[r][c], other.data[r][c]))
        return false;
  return true;
}

Matrix &
Matrix::operator=(const Matrix &other) {
  minorMask = other.minorMask;

  for (auto r = 0; r < 3; ++r)
    for (auto c = 0; c < 3; ++c)
      data[r][c] = other(r, c);
  return *this;
}

Matrix
Matrix::Transpose() const {
  Matrix transposed;
  if (minorMask.first == -1) {
    transposed(0, 0) = data[0][0];
    transposed(1, 0) = data[0][1];
    transposed(2, 0) = data[0][2];

    transposed(0, 1) = data[1][0];
    transposed(1, 1) = data[1][1];
    transposed(2, 1) = data[1][2];

    transposed(0, 2) = data[2][0];
    transposed(1, 2) = data[2][1];
    transposed(2, 2) = data[2][2];
  } else {
    // TODO
  }

  return transposed;
}

double
Matrix::Determinant() const {
  if (minorMask.first == -1) {
    return data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2]) -
           data[0][1] * (data[1][0] * data[2][2] - data[2][0] * data[1][2]) +
           data[0][2] * (data[1][0] * data[2][1] - data[2][0] * data[1][1]);
  } else {
    array<array<double, 2>, 2> vals;
    auto row = 0;
    auto col = 0;
    for (auto r = 0; r < 3; ++r) {
      if (r == minorMask.first)
        continue;
      for (auto c = 0; c < 3; ++c) {
        if (c == minorMask.second)
          continue;
        vals[row][col] = data[r][c];
        if (row == 0) {
          col = 1;
          continue;
        }
        if (col == 1) {
          row = 1;
          col = 0;
          continue;
        }
        if (row == 1) {
          col = 1;
          continue;
        }
      }
    }

    return vals[0][0] * vals[1][1] - vals[1][0] * vals[0][1];
  }
}

Matrix
Matrix::Identity() {
  return Matrix({{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}});
}

Matrix
Matrix::Submatrix(int row, int col) const {
  Matrix other(*this);
  other.minorMask = std::make_pair(row, col);
  return other;
}

double
Matrix::Minor(int row, int col) const {
  return Submatrix(row, col).Determinant();
}

double
Matrix::Cofactor(int row, int col) const {
  if ((row + col) % 2) {
    return -Minor(row, col);
  } else {
    return Minor(row, col);
  }
}

Matrix &
Matrix::Inverse() {
  if (inverse != nullptr)
    return *inverse;

  if (this->Determinant() == 0) {
    throw std::runtime_error(
        "Tried to take the inverse of a non-invertable matrix");
  }
  inverse = std::make_unique<Matrix>();

  auto det = Determinant();
  for (auto row = 0u; row < 3; ++row)
    for (auto col = 0u; col < 3; ++col)
      (*inverse)(row, col) = Cofactor(row, col) / det;

  return *inverse;
}
