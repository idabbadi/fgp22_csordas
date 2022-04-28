#include "Colour.h"
#include "config.h"
#include "helper/FileHandler.h"
#include "helper/Point.h"
#include "student/Face.h"
#include "student/HalfEdge.h"
#include "student/Mesh.h"
#include "student/Vertex.h"
#include <iostream>

int printUsage() {
  std::cerr << "Wrong way of calling the program!" << std::endl
            << "Usage: ./bin/fgp <command> <mesh> <params>" << std::endl
            << "Possible commands:" << std::endl
            << "- query" << std::endl
            << "- smoothing" << std::endl
            << "- decimation" << std::endl;

  exit(ERROR);
}

int printQueryUsage() {
  std::cerr << "Wrong way of calling the program!" << std::endl
            << "Usage: ./bin/fgp query <mesh> <query_number> <query_param(s)>"
            << std::endl
            << "Possible queries: " << std::endl
            << "- 3: faces adjacent to vertex (param: ID of vertex)"
            << std::endl
            << "- 4: vertices adjacent to face (param: ID of face)" << std::endl
            << "- 5: vertex at point (param: x, y, z as double)" << std::endl
            << "- 6: one ring neighbourhood (param: ID of vertex)" << std::endl
            << "Example: ./bin/fgp query res/meshes/cow.ply 4 0" << std::endl;

  exit(ERROR);
}

void printSmoothingUsage() {
  std::cerr << "Wrong way of calling the program!" << std::endl
            << "Usage: ./bin/fgp smoothing <mesh> <iterations> <lambda>"
            << std::endl
            << "Example: ./bin/fgp smoothing res/meshes/cow.ply 10 1"
            << std::endl;

  exit(ERROR);
}

void printDecimationUsage() {
  std::cerr << "Wrong way of calling the program!" << std::endl
            << "Usage: ./bin/fgp decimation <mesh> <percentage>" << std::endl
            << "Example: ./bin/fgp decimation res/meshes/cow.ply 10"
            << std::endl;

  exit(ERROR);
}

int executeQuery(Mesh *mesh, std::size_t query_code, std::size_t index,
                 const Point &point) {
  std::string output_path = "out/" + mesh->getMeshName() + "_" +
                            std::to_string(query_code) + "_" +
                            std::to_string(index) + ".log";
  Face *face = nullptr;
  Vertex *vertex = nullptr;

  std::vector<Vertex *> vertices;
  std::vector<Face *> faces;

  switch (query_code) {
  case 3:
    vertex = mesh->getVertex(index);
    if (vertex == nullptr) {
      std::cerr << "Error: the vertex you chose does not exist!" << std::endl;
      exit(ERROR);
    }
    vertex->setRed();

    faces = vertex->getAdjacentFaces();

    std::cout << "Result: ";
    for (auto &temp : faces)
      std::cout << std::to_string(temp->getID()) << " ";

    std::cout << std::endl;

    break;
  case 4:
    face = mesh->getFace(index);
    if (face == nullptr) {
      std::cerr << "Error: the face you chose does not exist!" << std::endl;
      exit(ERROR);
    }

    vertices = face->getAdjacentVertices();

    std::cout << "Result: ";
    for (auto &temp : vertices) {
      std::cout << std::to_string(temp->getID()) << " ";
      temp->setRed();
    }

    std::cout << std::endl;

    break;
  case 5:
    vertex = mesh->getVertexAtPosition(point);
    if (vertex == nullptr) {
      std::cerr << "Error: the vertex you chose does not exist!" << std::endl;
      exit(ERROR);
    }
    vertex->setRed();

    std::cout << "Result: " << std::to_string(vertex->getID()) << std::endl;

    break;
  case 6: {
    vertex = mesh->getVertex(index);
    if (vertex == nullptr) {
      std::cerr << "Error: the vertex you chose does not exist!" << std::endl;
      exit(ERROR);
    }
    vertex->setRed();

    vertices = vertex->getOneRingNeighbourhood();

    std::cout << "Result: ";
    for (auto &temp : vertices) {
      std::cout << std::to_string(temp->getID()) << " ";
      temp->setRed();
    }

    std::cout << std::endl;

    break;
  }
  default:
    std::cerr << "Query with given code does not exist!" << std::endl;
    exit(ERROR);
  }

  mesh->save(WORKING_DIR "out/" + mesh->getMeshName() + "_query_" +
             std::to_string(query_code) + "_" + std::to_string(index) + ".ply");
  return SUCCESS;
}

int executeSmoothing(Mesh *mesh, std::size_t iterations, double lambda) {
  for (std::size_t i = 0; i < iterations; ++i) {
    mesh->smooth(lambda);
  }
  mesh->smooth(lambda);

  mesh->save(WORKING_DIR "out/" + mesh->getMeshName() + "_smoothing_" +
             std::to_string(iterations) + "_" + std::to_string(lambda) +
             ".ply");

  std::cout << "Finished!" << std::endl;
  return SUCCESS;
}

int executeDecimation(Mesh *mesh, std::size_t percentage) {
  auto iterations =
      static_cast<std::size_t>(mesh->getVertexAmount() * (percentage / 100.0));
  for (std::size_t i = 0; i < iterations; i++) {
    mesh->decimate();
  }

  for (std::size_t i = 0; i < mesh->getVertexAmount(); i++) {
    auto vertex = mesh->getVertex(i);
    if (!vertex->isRemoved())
      vertex->setColor(Colour(vertex->getDistanceToAveragePlane(),
                              mesh->getMinDistanceToPlane(),
                              mesh->getMaxDistanceToPlane()));
  }

  mesh->save(WORKING_DIR "out/" + mesh->getMeshName() + "_decimation_" +
             std::to_string(percentage) + ".ply");

  std::cout << "Finished!" << std::endl;
  return SUCCESS;
}

int main(int argc, char *argv[]) {
// deactivate cout if logging is inactive
#ifndef LOGGING_ACTIVE
  std::cout.setstate(std::ios::failbit);
#endif

  if (argc < 4) {
    printUsage();
    return ERROR;
  }

  std::string command(argv[1]);

  std::string mesh_path = argv[2];

  std::string param_str = argv[3];
  std::size_t param_int = stoul(param_str);

  auto mesh = Mesh();
  mesh.load(mesh_path);

  if (command == "query") {
    if (argc == 5)
      return executeQuery(&mesh, param_int, std::stoul(argv[4]),
                          Point(0.0, 0.0, 0.0));
    else if (argc == 7)
      return executeQuery(
          &mesh, param_int, 0,
          Point(std::stod(argv[4]), std::stod(argv[5]), std::stod(argv[6])));
    else
      printQueryUsage();
  } else if (command == "smoothing") {
    if (argc == 5)
      return executeSmoothing(&mesh, param_int, std::stod(argv[4]));
    else
      printSmoothingUsage();
  } else if (command == "decimation") {
    if (argc == 4)
      return executeDecimation(&mesh, param_int);
    else
      printDecimationUsage();
  } else
    printUsage();

  return ERROR;
}
