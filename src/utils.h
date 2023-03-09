#pragma once

#include <array>

using std::array;

namespace cspflux {
// clang-format off
constexpr double PI    = 3.14159265358979323846;
constexpr double PI_2  = 1.57079632679489661923;
constexpr double PI_4  = 0.78539816339744830962;
constexpr double SQRT2 = 1.41421356237309504880;
//clang-format on
bool CompareDoubles(double, double);

  class Matrix {
  public:
    Matrix() {}
    Matrix(array<array<double, 3>, 3> input) { data = input; }
    Matrix(const Matrix &other) { data = other.data; }

    Matrix Transpose();

    static Matrix Identity();

    double Determinant();

    bool operator==(const Matrix&) const;
    const double& operator()(int, int) const;
    double& operator()(int, int);

  private:
    array<array<double, 3>, 3> data;
  };
}
