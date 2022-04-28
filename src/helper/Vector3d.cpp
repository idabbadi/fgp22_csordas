#include "Vector3d.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

const double EPSILON = 0.0001;

Vector3d::Vector3d(double d) {
  m_elements[0] = d;
  m_elements[1] = d;
  m_elements[2] = d;
}

Vector3d::Vector3d(double x, double y, double z) {
  m_elements[0] = x;
  m_elements[1] = y;
  m_elements[2] = z;
}

Vector3d::Vector3d(const Vector3d &rv) {
  m_elements[0] = rv[0];
  m_elements[1] = rv[1];
  m_elements[2] = rv[2];
}

Vector3d &Vector3d::operator=(const Vector3d &rv) {
  if (this != &rv) {
    m_elements[0] = rv[0];
    m_elements[1] = rv[1];
    m_elements[2] = rv[2];
  }
  return *this;
}

const double &Vector3d::operator[](std::size_t i) const {
  return m_elements[i];
}

double &Vector3d::operator[](std::size_t i) { return m_elements[i]; }

double Vector3d::x() const { return m_elements[0]; }

double Vector3d::y() const { return m_elements[1]; }

double Vector3d::z() const { return m_elements[2]; }

double Vector3d::abs() const {
  return sqrt(m_elements[0] * m_elements[0] + m_elements[1] * m_elements[1] +
              m_elements[2] * m_elements[2]);
}

void Vector3d::normalize() {
  double norm = abs();
  m_elements[0] /= norm;
  m_elements[1] /= norm;
  m_elements[2] /= norm;
}

Vector3d Vector3d::normalized() const {
  double norm = abs();
  return Vector3d(m_elements[0] / norm, m_elements[1] / norm,
                  m_elements[2] / norm);
}

Vector3d &Vector3d::operator+=(const Vector3d &v) {
  m_elements[0] += v.m_elements[0];
  m_elements[1] += v.m_elements[1];
  m_elements[2] += v.m_elements[2];
  return *this;
}

Vector3d &Vector3d::operator-=(const Vector3d &v) {
  m_elements[0] -= v.m_elements[0];
  m_elements[1] -= v.m_elements[1];
  m_elements[2] -= v.m_elements[2];
  return *this;
}

Vector3d &Vector3d::operator*=(double f) {
  m_elements[0] *= f;
  m_elements[1] *= f;
  m_elements[2] *= f;
  return *this;
}

double Vector3d::dot(const Vector3d &v0, const Vector3d &v1) {
  return v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2];
}

Vector3d Vector3d::cross(const Vector3d &v0, const Vector3d &v1) {
  return Vector3d(v0.y() * v1.z() - v0.z() * v1.y(),
                  v0.z() * v1.x() - v0.x() * v1.z(),
                  v0.x() * v1.y() - v0.y() * v1.x());
}

Vector3d operator+(const Vector3d &v0, const Vector3d &v1) {
  return Vector3d(v0[0] + v1[0], v0[1] + v1[1], v0[2] + v1[2]);
}

Vector3d operator-(const Vector3d &v0, const Vector3d &v1) {
  return Vector3d(v0[0] - v1[0], v0[1] - v1[1], v0[2] - v1[2]);
}

Vector3d operator*(const Vector3d &v0, const Vector3d &v1) {
  return Vector3d(v0[0] * v1[0], v0[1] * v1[1], v0[2] * v1[2]);
}

Vector3d operator/(const Vector3d &v0, const Vector3d &v1) {
  return Vector3d(v0[0] / v1[0], v0[1] / v1[1], v0[2] / v1[2]);
}

Vector3d operator-(const Vector3d &v) { return Vector3d(-v[0], -v[1], -v[2]); }

Vector3d operator*(double f, const Vector3d &v) {
  return Vector3d(v[0] * f, v[1] * f, v[2] * f);
}

Vector3d operator*(const Vector3d &v, double f) {
  return Vector3d(v[0] * f, v[1] * f, v[2] * f);
}

Vector3d operator/(const Vector3d &v, double f) {
  return Vector3d(v[0] / f, v[1] / f, v[2] / f);
}

bool operator==(const Vector3d &v0, const Vector3d &v1) {
  return std::abs(v0.x() - v1.x()) <= EPSILON &&
         std::abs(v0.y() - v1.y()) <= EPSILON &&
         std::abs(v0.z() - v1.z()) <= EPSILON;
}

bool operator!=(const Vector3d &v0, const Vector3d &v1) { return !(v0 == v1); }
