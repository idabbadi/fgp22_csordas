#include "Point.h"
#include <cmath>

const double EPSILON = 0.0001;

Point::Point(double x, double y, double z) : x_(x), y_(y), z_(z) {}

double Point::getX() { return x_; }
double Point::getY() { return y_; }
double Point::getZ() { return z_; }
Vector3d Point::getVector3d() { return Vector3d(x_, y_, z_); }

void Point::setX(double x) { x_ = x; }
void Point::setY(double y) { y_ = y; }
void Point::setZ(double z) { z_ = z; }
void Point::setVector3d(const Vector3d &vec) {
  x_ = vec.x();
  y_ = vec.y();
  z_ = vec.z();
}

bool operator==(Point point1, Point point2) {
  return std::abs(point1.x_ - point2.x_) <= EPSILON &&
         std::abs(point1.y_ - point2.y_) <= EPSILON &&
         std::abs(point1.z_ - point2.z_) <= EPSILON;
}
