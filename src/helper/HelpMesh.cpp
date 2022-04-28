#include "../student/Mesh.h"
#include "FileHandler.h"

void Mesh::save(const std::string &filename) {
  FileHandler::writeToPLYFile(this, filename);
}

std::string Mesh::getMeshName() { return mesh_name_; }

Face *Mesh::getFace(std::size_t id) const {
  return id < faces_.size() ? faces_[id] : nullptr;
}

Vertex *Mesh::getVertex(std::size_t id) const {
  return id < vertices_.size() ? vertices_[id] : nullptr;
}

HalfEdge *Mesh::getHalfEdge(std::size_t id) const {
  return id < half_edges_.size() ? half_edges_[id] : nullptr;
}

const std::size_t Mesh::getFaceAmount() const { return face_counter_; }

const std::size_t Mesh::getVertexAmount() const { return vertex_counter_; }

const std::size_t Mesh::getHalfEdgeAmount() const { return half_edge_counter_; }

const std::size_t Mesh::getNewFaceID() { return face_counter_++; }

const std::size_t Mesh::getNewHalfEdgeID() { return half_edge_counter_++; }

const std::size_t Mesh::getNewVertexID() { return vertex_counter_++; }

const std::size_t Mesh::getRemovedFacesAmount() const {
  return removed_faces_count_;
}

const std::size_t Mesh::getRemovedVerticesAmount() const {
  return removed_vertices_count_;
}

const double Mesh::getMinDistanceToPlane() const { return min_distance_; }

const double Mesh::getMaxDistanceToPlane() const { return max_distance_; }
