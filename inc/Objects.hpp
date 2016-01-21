#ifndef RT_OBJECTS_HPP
#define RT_OBJECTS_HPP

#include <sstream>

struct position {
  double x;
  double y;
  double z;

  position(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

class Objects {
public:
  Objects() = default;

  virtual bool intersect() const = 0;
  virtual bool parseArgs(std::stringstream &ss) = 0;
};

#endif /* end of include guard: RT_OBJECTS_HPP */
