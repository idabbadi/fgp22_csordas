#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <memory>
#include <string>
#include <vector>

class Triangle;
class QueryResult;
class Vector3d;
class Point;
class Colour;
class Mesh;
class Vertex;

class FileHandler {
public:
  FileHandler() = delete;
  static void writeToPLYFile(const Mesh *mesh,
                             const std::string &output_filename);
  static void readFromPLYFile(std::vector<std::shared_ptr<Point>> &point_vec,
                              std::vector<std::shared_ptr<Colour>> &color_vec,
                              std::vector<std::shared_ptr<Triangle>> &poly_vec,
                              const std::string &input_filename);
};

#endif // FILEHANDLER_H
