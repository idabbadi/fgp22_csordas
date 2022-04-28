#ifndef POINT_H
#define POINT_H

#include "Vector3d.h"

class Point {
public:
  Point(double x, double y, double z);

  double getX();
  double getY();
  double getZ();
  Vector3d getVector3d();

  void setX(double x);
  void setY(double y);
  void setZ(double z);
  void setVector3d(const Vector3d &vec);

  friend bool operator==(Point point1, Point point2);

protected:
  double x_;
  double y_;
  double z_;
};

#endif // POINT_H
