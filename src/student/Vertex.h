#ifndef VERTEX_H
#define VERTEX_H

#include "../helper/Vector3d.h"
#include "Colour.h"
#include <memory>
#include <vector>

class Point;
class HalfEdge;
class Face;

class Vertex {
public:
  // Constructors
  Vertex(const std::shared_ptr<Point> &pos,
         const std::shared_ptr<Colour> &color, std::size_t id);

  // Base Getter / Setter
  std::shared_ptr<Point> getPosition() const;
  HalfEdge *getHalfEdge() const;
  std::size_t getID() const;
  Colour getColor() const;
  Vector3d getVector3d() const;
  const double getROIArea() const;
  const Colour getLaPlaceSum() const;
  const Colour getLaPlaceOperator() const;
  const Vector3d getAverageNormal() const;
  const Vector3d getAveragePoint() const;
  const double getDistanceToAveragePlane() const;
  const bool isRemoved() const;

  void setPos(std::shared_ptr<Point> value);
  void setVector3d(const Vector3d &vec);
  void setHalfEdge(HalfEdge *value);
  void setID(std::size_t id);
  void setColor(Colour color);
  void setRed();
  void setROIArea(double area);
  void setLaPlaceSum(const Colour &sum);
  void setLaPlaceOperator(const Colour &op);
  void remove(std::size_t &counter);
  const std::vector<HalfEdge *> getAdjacentHalfEdges() const;
  const std::vector<Face *> getAdjacentFaces() const;
  const std::vector<Vertex *> getOneRingNeighbourhood() const;
  const bool isVertexAtPosition(const Point &pos) const;
  const double calcROIArea();
  const Colour calcLaPlaceSum();
  const Colour calcLaPlaceOperator();
  void applyLaPlaceOperator(double h, double lambda);
  const Vector3d calcAverageNormal();
  const Vector3d calcAveragePoint();
  const double calcDistanceToAveragePlane();
  const bool isInConvexNeighbourhood();

protected:
  std::shared_ptr<Point> pos_;
  HalfEdge *half_edge_;
  std::size_t id_;
  Colour color_;
  double roi_area_;
  Colour la_place_sum_;
  Colour la_place_operator_;
  Vector3d average_normal_;
  Vector3d average_point_;
  double distance_;
  bool removed_;
};

#endif // VERTEX_H
