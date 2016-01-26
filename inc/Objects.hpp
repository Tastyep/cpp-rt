#ifndef RT_OBJECTS_HPP
#define RT_OBJECTS_HPP

#include <sstream>
#include <array>

#include "Camera.hh"

class Objects {
public:
  Objects() = default;

  virtual double intersect(std::array<double, 3> rayVec, Camera camera) const = 0;
};

#endif /* end of include guard: RT_OBJECTS_HPP */
