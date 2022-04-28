#include "../student/Face.h"

const Vector3d Face::getNormal() const { return normal_; }
const Vector3d Face::getNormalizedNormal() const {
  return normal_.normalized();
}
const Vector3d Face::getCenter() const { return center_; }
const double Face::getArea() const { return area_; }
const std::size_t Face::getID() const { return id_; }
HalfEdge *Face::getHalfEdge() const { return half_edge_; }
const bool Face::isRemoved() const { return removed_; }

void Face::setID(std::size_t id) { id_ = id; }
void Face::setHalfEdge(HalfEdge *half_edge) { half_edge_ = half_edge; }
void Face::remove(std::size_t &counter) {
  half_edge_ = nullptr;
  removed_ = true;
  counter++;
}