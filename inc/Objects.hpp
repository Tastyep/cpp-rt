#ifndef RT_OBJECTS_HPP
#define RT_OBJECTS_HPP

#include <sstream>

class Objects {
public:
  Objects() = default;

  virtual bool intersect() const = 0;
  virtual bool parseArgs(std::stringstream &ss) = 0;
};

#endif /* end of include guard: RT_OBJECTS_HPP */
