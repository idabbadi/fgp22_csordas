#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <cstddef>

class Vertex;
class Face;

class HalfEdge {
public:
  // Constructors
  explicit HalfEdge(std::size_t id);
  HalfEdge(Vertex *origin, std::size_t id);
  HalfEdge(Vertex *origin, Face *face, std::size_t id);

  // Getter / Setter
  HalfEdge *getPrev() const;
  HalfEdge *getPair() const;
  HalfEdge *getNext() const;
  Vertex *getOrigin() const;
  Face *getFace() const;
  const std::size_t getID() const;
  const bool isRemoved() const;

  void setPrev(HalfEdge *prev);
  void setPair(HalfEdge *pair);
  void setNext(HalfEdge *next);
  void setOrigin(Vertex *origin);
  void setFace(Face *face);
  void setID(std::size_t id);
  void remove();

protected:
  HalfEdge *prev_;
  HalfEdge *next_;
  HalfEdge *pair_;
  Vertex *origin_;
  Face *face_;
  std::size_t id_;
  bool removed_;
};

#endif // HALFEDGE_H
