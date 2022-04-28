#ifndef Vector3D_H
#define Vector3D_H

#include <array>
#include <cstdio>

class Vector3d {
public:
  explicit Vector3d(double d = 0);
  Vector3d(double x, double y, double z);

  Vector3d(const Vector3d &rv);

  Vector3d &operator=(const Vector3d &rv);

  const double &operator[](std::size_t i) const;
  double &operator[](std::size_t i);

  double x() const;
  double y() const;
  double z() const;

  double abs() const;

  void normalize();
  Vector3d normalized() const;

  Vector3d &operator+=(const Vector3d &v);
  Vector3d &operator-=(const Vector3d &v);
  Vector3d &operator*=(double f);

  static double dot(const Vector3d &v0, const Vector3d &v1);
  static Vector3d cross(const Vector3d &v0, const Vector3d &v1);

protected:
  std::array<double, 3> m_elements;
};

Vector3d operator+(const Vector3d &v0, const Vector3d &v1);
Vector3d operator-(const Vector3d &v0, const Vector3d &v1);
Vector3d operator*(const Vector3d &v0, const Vector3d &v1);
Vector3d operator/(const Vector3d &v0, const Vector3d &v1);

Vector3d operator-(const Vector3d &v);

Vector3d operator*(double f, const Vector3d &v);
Vector3d operator*(const Vector3d &v, double f);
Vector3d operator/(const Vector3d &v, double f);

bool operator==(const Vector3d &v0, const Vector3d &v1);
bool operator!=(const Vector3d &v0, const Vector3d &v1);

#endif // Vector3D_H
