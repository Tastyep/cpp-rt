#ifndef RT_OBJECTS_HPP
#define RT_OBJECTS_HPP

#include <array>
#include <sstream>

#include "Camera.hh"

class Objects {
public:
  Objects() = default;

  virtual double intersect(Vector rayVec, Camera camera) const = 0;
};

#endif /* end of include guard: RT_OBJECTS_HPP */
