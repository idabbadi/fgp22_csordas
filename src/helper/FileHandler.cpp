#include "FileHandler.h"
#include "../config.h"
#include "../student/Face.h"
#include "../student/HalfEdge.h"
#include "../student/Mesh.h"
#include "../student/Vertex.h"
#include "Colour.h"
#include "Point.h"
#include "Triangle.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

void FileHandler::readFromPLYFile(
    std::vector<std::shared_ptr<Point>> &point_vec,
    std::vector<std::shared_ptr<Colour>> &color_vec,
    std::vector<std::shared_ptr<Triangle>> &poly_vec,
    const std::string &input_filename) {
  std::size_t face_count, vertex_count;
  std::string line;

  std::ifstream input_file;
  input_file.open(input_filename, std::ifstream::in);

  if (!input_file.is_open()) {
    std::cerr << "Cannot open your given PLY file: " << input_filename
              << std::endl;
    exit(ERROR);
  }

  getline(input_file, line);
  while (line != "vertex")
    getline(input_file, line, ' ');

  input_file >> vertex_count;

  while (line != "face")
    getline(input_file, line, ' ');

  input_file >> face_count;

  while (line.compare(0, 10, "end_header") != 0)
    getline(input_file, line);

  for (std::size_t i = 0; i < vertex_count; i++) {
    std::string coord_line;
    getline(input_file, coord_line);
    std::istringstream iss(coord_line);
    double x, y, z;
    iss >> x;
    iss >> y;
    iss >> z;
    point_vec.push_back(std::make_shared<Point>(x, y, z));
    unsigned int r, g, b;
    iss >> r;
    iss >> g;
    iss >> b;
    color_vec.push_back(std::make_shared<Colour>(
        (double)r / 255., (double)g / 255., (double)b / 255.));
  }

  for (std::size_t i = 0; i < face_count; i++) {
    std::string face_line;
    std::size_t num_corners;

    getline(input_file, face_line);
    std::istringstream iss(face_line);

    iss >> num_corners;

    if (num_corners != 3) {
      std::cerr << "PLY file must contain triangles!" << std::endl;
      exit(ERROR);
    }

    std::array<std::size_t, 3> corners = {0};
    for (std::size_t j = 0; j < num_corners; j++)
      iss >> corners[j];

    poly_vec.push_back(std::make_shared<Triangle>(corners));
  }

  input_file.close();
}
void FileHandler::writeToPLYFile(const Mesh *mesh,
                                 const std::string &output_filename) {
  std::ofstream myfile(output_filename);
  if (!myfile.is_open()) {
    std::cerr << "invalid file name " << output_filename << std::endl;
    return;
  }

  myfile << "ply" << std::endl;
  myfile << "format ascii 1.0" << std::endl;
  myfile << "element vertex " << mesh->getVertexAmount() << std::endl;
  myfile << "property float x" << std::endl;
  myfile << "property float y" << std::endl;
  myfile << "property float z" << std::endl;
  myfile << "property uchar red " << std::endl;
  myfile << "property uchar green " << std::endl;
  myfile << "property uchar blue " << std::endl;
  myfile << "element face "
         << (mesh->getFaceAmount() - mesh->getRemovedFacesAmount())
         << std::endl;
  myfile << "property list uchar int vertex_index" << std::endl;
  myfile << "end_header" << std::endl;

  for (std::size_t i = 0; i < mesh->getVertexAmount(); i++) {
    auto vertex = mesh->getVertex(i);
    auto pos = vertex->getPosition();
    auto col = vertex->getColor();
    auto r = static_cast<unsigned int>(
        std::round(std::min(1., std::max(0., col.getR())) * 255.));
    auto g = static_cast<unsigned int>(
        std::round(std::min(1., std::max(0., col.getG())) * 255.));
    auto b = static_cast<unsigned int>(
        std::round(std::min(1., std::max(0., col.getB())) * 255.));
    myfile << pos->getX() << " " << pos->getY() << " " << pos->getZ() << " "
           << r << " " << g << " " << b << std::endl;
  }

  for (std::size_t i = 0; i < mesh->getFaceAmount(); i++) {
    auto face = mesh->getFace(i);
    if (face->isRemoved())
      continue;

    auto currentHf = face->getHalfEdge();
    int vertexCountOfFace = 1;

    while (currentHf->getNext() != face->getHalfEdge()) {
      vertexCountOfFace++;
      currentHf = currentHf->getNext();
    }

    myfile << vertexCountOfFace << " ";

    currentHf = face->getHalfEdge();
    while (currentHf->getNext() != face->getHalfEdge()) {
      myfile << currentHf->getOrigin()->getID() << " ";
      currentHf = currentHf->getNext();
    }
    myfile << currentHf->getOrigin()->getID();
    myfile << std::endl;
  }

  myfile.close();
}
