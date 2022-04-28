#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>

class Triangle {
public:
  explicit Triangle(std::array<std::size_t, 3> corners);

  std::array<std::size_t, 3> getCorners();
  void setCorners(std::array<std::size_t, 3> corners);

protected:
  std::array<std::size_t, 3> corners_;
};

#endif // TRIANGLE_H
