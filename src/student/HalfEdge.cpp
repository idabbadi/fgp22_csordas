#include "HalfEdge.h"

HalfEdge::HalfEdge(Vertex *origin, Face *face, std::size_t id)
    : prev_(nullptr), next_(nullptr), pair_(nullptr), origin_(origin),
      face_(face), id_(id), removed_(false) {}

HalfEdge::HalfEdge(Vertex *origin, std::size_t id)
    : prev_(nullptr), next_(nullptr), pair_(nullptr), origin_(origin),
      face_(nullptr), id_(id), removed_(false) {}

HalfEdge::HalfEdge(std::size_t id)
    : prev_(nullptr), next_(nullptr), pair_(nullptr), origin_(nullptr),
      face_(nullptr), id_(id), removed_(false) {}