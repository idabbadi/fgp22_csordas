#include "Triangle.h"

Triangle::Triangle(std::array<std::size_t, 3> corners) : corners_(corners) {}

std::array<std::size_t, 3> Triangle::getCorners() { return corners_; }

void Triangle::setCorners(std::array<std::size_t, 3> corners) {
  corners_ = corners;
}
