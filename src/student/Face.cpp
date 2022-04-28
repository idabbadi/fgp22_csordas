#include "Face.h"
#include "HalfEdge.h"
#include "Vertex.h"
#include <cstring>
#include <string>
#include <stdexcept>
#define __FILENAME__                                                           \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

Face::Face(std::size_t id)
    : half_edge_(nullptr), id_(id), normal_(0), area_(0), center_(0),
      removed_(false) {}

// TODO
const std::vector<HalfEdge *> Face::getAdjacentHalfEdges() const {
  std::vector<HalfEdge *> adjacent_edges_;
  HalfEdge* adjacent = half_edge_;
  adjacent_edges_.push_back(adjacent);
  adjacent = adjacent->getNext();
  adjacent_edges_.push_back(adjacent);
  adjacent = adjacent->getNext();
  adjacent_edges_.push_back(adjacent);
  return adjacent_edges_;
}


// TODO
const std::vector<Vertex *> Face::getAdjacentVertices() const {
  std::vector<Vertex*> vertices;
  HalfEdge* current_half_edge = half_edge_;
  do
  {
    vertices.push_back(current_half_edge->getOrigin());
    current_half_edge = current_half_edge->getNext();
  }
  while(current_half_edge != half_edge_);

  return vertices;
} 


// TODO
const Vector3d Face::calcNormal() {
  // TODO calculate and populate normal_
  const std::vector<Vertex*> vertices = getAdjacentVertices();
  std::vector<Vector3d> corners;
  for(auto vertex : vertices)
  {
    corners.push_back(vertex->getVector3d());
  }
  normal_ = Vector3d::cross(corners.at(1) - corners.at(0), corners.at(2) - corners.at(1));
  return normal_;
}

// TODO
const double Face::calcArea() {
  // TODO calculate and populate area_

  Vector3d normal_vect = calcNormal();
  area_ = normal_vect.abs() / 2;
  return area_;
}
  /*
  area_ = getNormal().abs() / 2;
  return area_;
}

*/
// TODO
const Vector3d Face::calcCenter() {
  // TODO calculate and populate center_

    const std::vector<Vertex *> adjacent_vertices = getAdjacentVertices();
  Vector3d temp;
  for(Vertex* vertex : adjacent_vertices)
  {
    temp += vertex->getVector3d();
  }
  center_ = temp / 3;
  return center_;
}

  /*
  const std::vector<Vertex*> vertices = getAdjacentVertices();
  Vector3d sum_of_vertices;
  for(Vertex* vertex : vertices)
  {
    sum_of_vertices += vertex->getVector3d();
  }
  center_ = sum_of_vertices / 3;
  return center_;
}
*/
