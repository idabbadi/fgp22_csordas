#ifndef MESH_H
#define MESH_H

#include <map>
#include <memory>
#include <string>
#include <vector>

class Point;
class Triangle;
class Colour;
class HalfEdge;
class Vertex;
class Face;

class Mesh {
public:
  // Constructors
  Mesh();

  // Destructors
  ~Mesh();

  // Helper
  void load(const std::string &filename);
  void save(const std::string &filename);

  // Getter / Setter
  std::string getMeshName();
  HalfEdge *getHalfEdge(std::size_t id) const;
  Vertex *getVertex(std::size_t id) const;
  Face *getFace(std::size_t id) const;
  const std::size_t getHalfEdgeAmount() const;
  const std::size_t getVertexAmount() const;
  const std::size_t getFaceAmount() const;
  const std::size_t getRemovedFacesAmount() const;
  const std::size_t getRemovedVerticesAmount() const;
  const double getMinDistanceToPlane() const;
  const double getMaxDistanceToPlane() const;

protected:
  const std::size_t getNewFaceID();
  const std::size_t getNewHalfEdgeID();
  const std::size_t getNewVertexID();

public:
  void load(std::vector<std::shared_ptr<Point>> &point_vec,
            std::vector<std::shared_ptr<Colour>> &color_vec,
            std::vector<std::shared_ptr<Triangle>> &poly_vec);
  Vertex *getVertexAtPosition(const Point &pos);
  void smooth(double lambda);
  void decimate();
  Vertex *findSuitableVertex();
  void removeVertex(Vertex *vertex);


protected:
  std::size_t face_counter_;
  std::size_t half_edge_counter_;
  std::size_t vertex_counter_;
  std::string mesh_name_;
  std::vector<HalfEdge *> half_edges_;
  std::vector<Vertex *> vertices_;
  std::vector<Face *> faces_;
  double min_distance_;
  double max_distance_;
  std::size_t removed_vertices_count_;
  std::size_t removed_faces_count_;
};

#endif // MESH_H
