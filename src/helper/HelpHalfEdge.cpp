#include "../student/HalfEdge.h"

HalfEdge *HalfEdge::getPrev() const { return prev_; }
HalfEdge *HalfEdge::getPair() const { return pair_; }
HalfEdge *HalfEdge::getNext() const { return next_; }
Vertex *HalfEdge::getOrigin() const { return origin_; }
Face *HalfEdge::getFace() const { return face_; }
const std::size_t HalfEdge::getID() const { return id_; }
const bool HalfEdge::isRemoved() const { return removed_; }

void HalfEdge::setPrev(HalfEdge *prev) {
  prev_ = prev;
  if (prev && !prev->getNext())
    prev->setNext(this);
}

void HalfEdge::setPair(HalfEdge *pair) {
  pair_ = pair;
  if (pair && !pair->getPair())
    pair->setPair(this);
}

void HalfEdge::setNext(HalfEdge *next) {
  next_ = next;
  if (next && !next->getPrev())
    next->setPrev(this);
}

void HalfEdge::setOrigin(Vertex *origin) { origin_ = origin; }
void HalfEdge::setFace(Face *face) { face_ = face; }
void HalfEdge::setID(std::size_t id) { id_ = id; }
void HalfEdge::remove() {
  prev_ = nullptr;
  pair_ = nullptr;
  next_ = nullptr;
  face_ = nullptr;
  origin_ = nullptr;
  removed_ = true;
}
