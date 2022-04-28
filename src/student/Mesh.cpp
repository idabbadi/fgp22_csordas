#include "Mesh.h"
#include "../helper/FileHandler.h"
#include "../helper/Point.h"
#include "../helper/Triangle.h"
#include "Face.h"
#include "HalfEdge.h"
#include "Vertex.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>

#define __FILENAME__                                                           \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

Mesh::Mesh()

    : face_counter_(0), half_edge_counter_(0), vertex_counter_(0),
      min_distance_(0), max_distance_(0), removed_vertices_count_(0),
      removed_faces_count_(0) {}

Mesh::~Mesh() {
  auto del = [](auto x) { delete x; };
  std::for_each(vertices_.begin(), vertices_.end(), del);
  std::for_each(faces_.begin(), faces_.end(), del);
  std::for_each(half_edges_.begin(), half_edges_.end(), del);
}

void Mesh::load(const std::string &filename) {
  mesh_name_ = filename;
  if (mesh_name_.rfind('/') != std::string::npos)
    mesh_name_ = mesh_name_.substr(mesh_name_.rfind('/') + 1);

  std::vector<std::shared_ptr<Point>> point_vec;
  std::vector<std::shared_ptr<Colour>> color_vec;
  std::vector<std::shared_ptr<Triangle>> poly_vec;
  FileHandler::readFromPLYFile(point_vec, color_vec, poly_vec, filename);
  load(point_vec, color_vec, poly_vec);
}

// TODO
void Mesh::load(std::vector<std::shared_ptr<Point>> &point_vec,
                std::vector<std::shared_ptr<Colour>> &color_vec,
                std::vector<std::shared_ptr<Triangle>> &poly_vec) {
  // TODO fill vectors vertices_, faces_, and half_edges_. Use getNewVertexID(),
  // getNewFaceID(), and getNewHalfEdgeID()

 for (long unsigned int i = 0; i < point_vec.size(); i++)
{
 Vertex* newvertex = new Vertex(point_vec [i], color_vec[i], getNewVertexID());
 vertices_.push_back(newvertex);
}

std::map<std::pair<size_t, std::size_t>, HalfEdge*> halfedgemap;
std::map<char,int>::iterator it;

for (long unsigned int i = 0; i < poly_vec.size(); i++)
{
  Face* newface = new Face(getNewFaceID());

  auto corner_array = poly_vec[i].get()->getCorners();
    
  HalfEdge* firsthalfedge = new HalfEdge(vertices_[corner_array[0]], newface, getNewHalfEdgeID());  
 
  HalfEdge* secondhalfedge = new HalfEdge(vertices_[corner_array[1]], newface, getNewHalfEdgeID());  
  
  HalfEdge* thirdhalfedge = new HalfEdge(vertices_[corner_array[2]], newface, getNewHalfEdgeID()); 


  Vertex* vertexone = vertices_.at(corner_array[0]);
  vertexone->setHalfEdge(firsthalfedge);  

  Vertex* vertextwo = vertices_.at(corner_array[1]);
  vertextwo->setHalfEdge(secondhalfedge);  

  Vertex* vertexthree = vertices_.at(corner_array[2]);
  vertexthree->setHalfEdge(thirdhalfedge);  

  firsthalfedge->setOrigin(vertexone);
  secondhalfedge->setOrigin(vertextwo);
  thirdhalfedge->setOrigin(vertexthree);

  firsthalfedge->setNext(secondhalfedge);
  secondhalfedge->setNext(thirdhalfedge);
  thirdhalfedge->setNext(firsthalfedge);

  thirdhalfedge->setPrev(secondhalfedge);
  secondhalfedge->setPrev(firsthalfedge);
  firsthalfedge->setPrev(thirdhalfedge);

  newface->setHalfEdge(firsthalfedge);  
    
  auto searchone = halfedgemap.find(std::make_pair(corner_array[1],corner_array[0]));
  if(searchone != halfedgemap.end())
  {
    firsthalfedge->setPair(searchone->second);
  }
  else{
    halfedgemap.insert(std::pair<std::pair<size_t, size_t>, HalfEdge*>(std::make_pair(corner_array[0],corner_array[1]),firsthalfedge));
  }

  auto searchtwo= halfedgemap.find(std::make_pair(corner_array[2],corner_array[1]));
  if(searchtwo != halfedgemap.end())
  {
    secondhalfedge->setPair(searchtwo->second);
  }
  else{
    halfedgemap.insert(std::pair<std::pair<size_t, size_t>, HalfEdge*>(std::make_pair(corner_array[1],corner_array[2]),secondhalfedge));
  }

  auto searchthree= halfedgemap.find(std::make_pair(corner_array[0],corner_array[2]));
  if(searchthree != halfedgemap.end())
  {
   thirdhalfedge->setPair(searchthree->second);
  }
  else{
    halfedgemap.insert(std::pair<std::pair<size_t, size_t>, HalfEdge*>(std::make_pair(corner_array[2],corner_array[0]),thirdhalfedge));
  }

  half_edges_.push_back(firsthalfedge);
  half_edges_.push_back(secondhalfedge);
  half_edges_.push_back(thirdhalfedge);

  faces_.push_back(newface);
  
}

}


// TODO
Vertex *Mesh::getVertexAtPosition(const Point &pos) {
  // TODO return nullptr if there is no vertex at the given position
  for (auto vertex : vertices_)
  {
    
    if(vertex->isVertexAtPosition(pos))
    {
      return vertex;
    }
  
  }
  return nullptr;
}



// TODO
void Mesh::smooth(double lambda) {
  throw std::runtime_error("TODO: Implement " + std::string(__FUNCTION__) +
                           "(...) in " + std::string(__FILENAME__));
}

// TODO
void Mesh::decimate() {
  // TODO calculate and populate min_distance_ and max_distance_
min_distance_ = std::numeric_limits<double>::max();
  max_distance_ = 0;
  for(Face* face : faces_)
  {
    if(face->isRemoved())
    {
      continue;
    }
    face->calcCenter();
    face->calcArea();
    face->calcNormal();
  }
  for(Vertex* vertex : vertices_)
  {
    if(vertex->isRemoved())
    {
      continue;
    }
    
    vertex->calcAverageNormal();
    vertex->calcAveragePoint();
    
    double distance = vertex->calcDistanceToAveragePlane();
    min_distance_ = std::min(min_distance_, distance);
    max_distance_ = std::max(max_distance_, distance);
  }
  Vertex* suitable_vertex = findSuitableVertex();
  if(suitable_vertex != nullptr)
  {
    removeVertex(suitable_vertex);
  }
}

// TODO
Vertex *Mesh::findSuitableVertex() {
  // TODO return nullptr if there is no suitable vertex

  std::vector<Vertex*> sorted_vertices;
  for(Vertex* vertex : vertices_)
  {
    if(!vertex->isRemoved())
    {
      sorted_vertices.push_back(vertex);
    }
  }

  std::stable_sort(sorted_vertices.begin(), sorted_vertices.end(),
  [](Vertex* vertex_1, Vertex* vertex_2) -> bool{return vertex_1->getDistanceToAveragePlane() < vertex_2->getDistanceToAveragePlane();});

  for(Vertex* vertex : sorted_vertices)
  {
    if(vertex->isInConvexNeighbourhood())
    {
      return vertex;
    }
  }
  return nullptr;
}


  /*
std::vector<Vertex*> vertices_sorted = vertices_;
  std::sort(vertices_sorted.begin(), vertices_sorted.end(), [](Vertex* v1, Vertex* v2) -> bool{return v1->getDistanceToAveragePlane() < v2->getDistanceToAveragePlane();});

  for(Vertex* vertex : vertices_sorted)
  {  
    if(!vertex->isRemoved() && vertex->isInConvexNeighbourhood() && vertex->getOneRingNeighbourhood().size() >= 3)
    {
      return vertex;
    }
  }
  return nullptr;
}
*/
// TODO
void Mesh::removeVertex(Vertex *vertex) {
  // TODO use HalfEdge::remove(), Face::remove(), Vertex::remove(),
  // removed_faces_count_, and removed_vertices_count_

  std::vector<Vertex*> orn = vertex->getOneRingNeighbourhood();
  std::vector<HalfEdge*> adjacent_half_edges = vertex->getAdjacentHalfEdges();

  if(adjacent_half_edges.size() == 3)
  {
    Face* face = new Face(getNewFaceID());
    faces_.push_back(face);

    for(auto he : adjacent_half_edges)
    {
      HalfEdge* outer_half_edge = he->getNext();
      outer_half_edge->getOrigin()->setHalfEdge(outer_half_edge);
      outer_half_edge->setPrev(he->getPair()->getPrev());
      outer_half_edge->setNext(outer_half_edge->getNext()->getPair()->getNext());
      he->setFace(face);
      face->setHalfEdge(outer_half_edge);
    }
    
  }
  else
  {
    Face* face = new Face(getNewFaceID());
    faces_.push_back(face);
    
    HalfEdge* he0 = adjacent_half_edges.at(0)->getNext();
    HalfEdge* he1 = adjacent_half_edges.at(1)->getNext();
    HalfEdge* he2 = new HalfEdge(orn.at(2), face, getNewHalfEdgeID());
    half_edges_.push_back(he2);

    he0->setFace(face);
    he1->setFace(face);

    he0->setNext(he1);
    he1->setNext(he2);
    he2->setNext(he0);

    he0->getOrigin()->setHalfEdge(he0);
    he1->getOrigin()->setHalfEdge(he1);

    face->setHalfEdge(he2);


    for(std::size_t counter = 2; counter < adjacent_half_edges.size() - 2; counter++)
    {
      HalfEdge* pair = he2;
      
      Face* face = new Face(getNewFaceID());
      faces_.push_back(face);

      he0 = new HalfEdge(orn.at(0), face, getNewHalfEdgeID());
      half_edges_.push_back(he0);

      he0->setPair(pair);

      he1 = adjacent_half_edges.at(counter)->getNext();
      he2 = new HalfEdge(orn.at(counter + 1), face, getNewHalfEdgeID());
      half_edges_.push_back(he2);

      he0->setNext(he1);
      he1->setNext(he2);
      he2->setNext(he0);

      he1->setFace(face);
      he1->getOrigin()->setHalfEdge(he1);

      face->setHalfEdge(he2);

    }

    HalfEdge* pair = he2;

    face = new Face(getNewFaceID());
    faces_.push_back(face);

    he0 = adjacent_half_edges.at(adjacent_half_edges.size() - 2)->getNext();
    he1 = adjacent_half_edges.at(adjacent_half_edges.size() - 1)->getNext();
    he2 = new HalfEdge(orn.at(0), face, getNewHalfEdgeID());
    half_edges_.push_back(he2);

    he0->setFace(face);
    he1->setFace(face);

    he0->setNext(he1);
    he1->setNext(he2);
    he2->setNext(he0);

    he0->getOrigin()->setHalfEdge(he0);
    he1->getOrigin()->setHalfEdge(he1);

    face->setHalfEdge(he2);

    he2->setPair(pair);
    
  }

  for(auto he : adjacent_half_edges)
  {
    he->getFace()->remove(removed_faces_count_);
    he->getPair()->remove();
    he->remove();
  }

  vertex->remove(removed_vertices_count_);
}

