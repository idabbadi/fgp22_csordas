#include "Vertex.h"
#include "../helper/Point.h"
#include "Colour.h"
#include "Face.h"
#include "HalfEdge.h"
#include "Util.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <utility>
#include <stdexcept>
#define __FILENAME__                                                           \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

Vertex::Vertex(const std::shared_ptr<Point> &pos,
               const std::shared_ptr<Colour> &color, std::size_t id)
    : pos_(std::move(pos)), half_edge_(), id_(id),
      color_(color->getR(), color->getG(), color->getB()), roi_area_(0),
      la_place_sum_(0, 0, 0), la_place_operator_(0, 0, 0), average_normal_(0),
      average_point_(0), distance_(0), removed_(false) {}

// TODO
const std::vector<HalfEdge *> Vertex::getAdjacentHalfEdges() const {
  std::vector<HalfEdge*> half_edges;
  HalfEdge* current_half_edge = half_edge_;
  do
  {
    half_edges.push_back(current_half_edge);
    current_half_edge = current_half_edge->getPrev()->getPair();
  } while (current_half_edge != half_edge_);
  return half_edges;
}


// TODO
const std::vector<Face *> Vertex::getAdjacentFaces() const {
  std::vector<Face *> adjacent_faces;
  HalfEdge* start = getHalfEdge();
  adjacent_faces.push_back(start->getFace());

  for(HalfEdge* current_half_edge = start->getPrev()->getPair(); current_half_edge != start;
      current_half_edge = current_half_edge->getPrev()->getPair())
  {
    adjacent_faces.push_back(current_half_edge->getFace());
  }
  return adjacent_faces;
}

  /*
  std::vector<Face*> faces;
  HalfEdge* current_half_edge = half_edge_;

  do
  {
    faces.push_back(current_half_edge->getFace());
    current_half_edge = current_half_edge->getPrev()->getPair();
  } while (current_half_edge != half_edge_);
  
  return faces;
}
*/

// TODO
const std::vector<Vertex *> Vertex::getOneRingNeighbourhood() const {
  std::vector<Vertex *> vertices;
  HalfEdge* current_half_edge = half_edge_;

  do
  {    
    current_half_edge = current_half_edge->getNext();
    vertices.push_back(current_half_edge->getOrigin());
    current_half_edge = current_half_edge->getNext()->getPair();
  } while (current_half_edge != half_edge_);

  return vertices;
}

// TODO
const bool Vertex::isVertexAtPosition(const Point &pos) const {
  
  return pos == *pos_.get(); 
                           
}

// TODO
const double Vertex::calcROIArea() {
  // TODO calculate and populate roi_area_
  throw std::runtime_error("TODO: Implement " + std::string(__FUNCTION__) +
                           "(...) in " + std::string(__FILENAME__));
}

// TODO
const Colour Vertex::calcLaPlaceSum() {
  // TODO calculate and populate la_place_sum_
  throw std::runtime_error("TODO: Implement " + std::string(__FUNCTION__) +
                           "(...) in " + std::string(__FILENAME__));
}

// TODO
const Colour Vertex::calcLaPlaceOperator() {
  // TODO calculate and populate la_place_operator_
  throw std::runtime_error("TODO: Implement " + std::string(__FUNCTION__) +
                           "(...) in " + std::string(__FILENAME__));
}

// TODO
void Vertex::applyLaPlaceOperator(const double h, const double lambda) {
  throw std::runtime_error("TODO: Implement " + std::string(__FUNCTION__) +
                           "(...) in " + std::string(__FILENAME__));
}

// TODO
const Vector3d Vertex::calcAverageNormal() {
  // TODO calculate and populate average_normal_
  const std::vector<Face*> faces = getAdjacentFaces();
  Vector3d normal_sum;
  double area_sum = 0;

  for(Face* face : faces)
  {
    double area = face->getArea();
    normal_sum += area * face->getNormalizedNormal();
    area_sum += area;
  }
  average_normal_ = normal_sum / area_sum;
  return average_normal_;
}

// TODO
const Vector3d Vertex::calcAveragePoint() {

const std::vector<Face*> adjacent_faces = getAdjacentFaces();
  Vector3d sum_weighted_centers = sum_weighted_centers;
  double sum_area = 0;

  for(Face* face : adjacent_faces)
  {
    double area = face->getArea();
    sum_weighted_centers += area * face->getCenter();
    sum_area += area;
  }
  return average_point_ = sum_weighted_centers / sum_area;
}


  /*
  // TODO calculate and populate average_point_
  const std::vector<Face*> faces = getAdjacentFaces();
  Vector3d centers_sum;
  double area_sum = 0;

  for(Face* face : faces)
  {
    double area = face->getArea();
    centers_sum += area * face->getCenter();
    area_sum += area;
  }
  average_point_ = centers_sum / area_sum;
  return average_point_;
}
*/
// TODO
const double Vertex::calcDistanceToAveragePlane() {
  // TODO calculate and populate distance_
  distance_ = std::abs(Vector3d::dot((getVector3d() - getAveragePoint()), getAverageNormal().normalized()));
  return distance_;
}

// TODO
const bool Vertex::isInConvexNeighbourhood() {
  std::vector<Vertex*> orn = getOneRingNeighbourhood();
  for(std::size_t counter = 0; counter < orn.size(); counter++)
  {
    std::size_t previous_index = counter - 1;
    std::size_t next_index = counter + 1;
    if(counter == 0)
    {
      previous_index = orn.size() - 1;
    }
    if(counter == orn.size() - 1)
    {
      next_index = 0;
    }
    Vector3d previous_vertex = orn.at(previous_index)->getVector3d();
    Vector3d current_vertex = orn.at(counter)->getVector3d();
    Vector3d next_vertex = orn.at(next_index)->getVector3d();
    double sinus = Vector3d::dot(Vector3d::cross(current_vertex - previous_vertex, next_vertex - current_vertex), getAverageNormal());
    if(sinus < 0)
    {
      return false;
    }
  }
  return true;
}

