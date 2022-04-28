#ifndef FACE_H
#define FACE_H

#include "../helper/Vector3d.h"
#include <vector>

class HalfEdge;
class Vertex;

class Face {
public:
  // Constructors
  explicit Face(std::size_t id);

  // Getter / Setter
  HalfEdge *getHalfEdge() const;
  const std::size_t getID() const;
  const double getArea() const;
  const Vector3d getNormal() const;
  const Vector3d getNormalizedNormal() const;
  const Vector3d getCenter() const;
  const bool isRemoved() const;

  void setHalfEdge(HalfEdge *half_edge);
  void setID(std::size_t id);
  void remove(std::size_t &counter);

  const std::vector<HalfEdge *> getAdjacentHalfEdges() const;
  const std::vector<Vertex *> getAdjacentVertices() const;
  const Vector3d calcNormal();
  const double calcArea();
  const Vector3d calcCenter();

protected:
  HalfEdge *half_edge_;
  std::size_t id_;
  Vector3d normal_;
  double area_;
  Vector3d center_;
  bool removed_;
};

#endif // FACE_H
