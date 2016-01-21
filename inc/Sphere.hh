#ifndef RT_SPHERE_HH
#define RT_SPHERE_HH

#include "SceneObj.hh"

class Sphere : public SceneObj {
public:
  Sphere();

  ~Sphere() = default;
  Sphere(const Sphere &other) = default;
  Sphere(Sphere &&other) = default;
  Sphere &operator=(const Sphere &other) = default;
  Sphere &operator=(Sphere &&other) = default;

  bool intersect() const;
  bool parseArgs(std::stringstream &ss);

private:
  unsigned int radius = 0;
  unsigned int color = 0;
  position pos;
};

#endif /* end of include guard: RT_SPHERE_HH */
