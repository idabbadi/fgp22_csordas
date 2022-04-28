#include "../student/Vertex.h"
#include "Colour.h"
#include "Point.h"
#include <iostream>

std::shared_ptr<Point> Vertex::getPosition() const { return pos_; }
HalfEdge *Vertex::getHalfEdge() const { return half_edge_; }
std::size_t Vertex::getID() const { return id_; }

void Vertex::setPos(std::shared_ptr<Point> value) { pos_ = std::move(value); }
void Vertex::setHalfEdge(HalfEdge *value) { half_edge_ = value; }
void Vertex::setID(std::size_t id) { id_ = id; }
const double Vertex::getDistanceToAveragePlane() const { return distance_; }

const Vector3d Vertex::getAveragePoint() const { return average_point_; }

const Vector3d Vertex::getAverageNormal() const { return average_normal_; }

const bool Vertex::isRemoved() const { return removed_; }

void Vertex::remove(std::size_t &counter) {
  half_edge_ = nullptr;
  removed_ = true;
  counter++;
}

const Colour Vertex::getLaPlaceOperator() const { return la_place_operator_; }

void Vertex::setROIArea(double area) { roi_area_ = area; }

void Vertex::setLaPlaceSum(const Colour &sum) { la_place_sum_ = sum; }

void Vertex::setLaPlaceOperator(const Colour &op) { la_place_operator_ = op; }

Vector3d Vertex::getVector3d() const { return pos_->getVector3d(); }

const double Vertex::getROIArea() const { return roi_area_; }
const Colour Vertex::getLaPlaceSum() const { return la_place_sum_; }
Colour Vertex::getColor() const { return color_; }
void Vertex::setColor(Colour color) { color_ = color; }

void Vertex::setRed() { setColor(Colour(1., 0., 0.)); }

void Vertex::setVector3d(const Vector3d &vec) { pos_->setVector3d(vec); }
