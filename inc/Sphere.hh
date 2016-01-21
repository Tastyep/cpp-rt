#ifndef RT_SPHERE_HH
#define RT_SPHERE_HH

#include "Objects.hpp"

class Sphere : public Objects {
public:
  Sphere() = default;

  ~Sphere() = default;
  Sphere(const Sphere &other) = default;
  Sphere(Sphere &&other) = default;
  Sphere &operator=(const Sphere &other) = default;
  Sphere &operator=(Sphere &&other) = default;

  bool intersect() const;
  bool parseArgs(std::stringstream &ss);
};

#endif /* end of include guard: RT_SPHERE_HH */
