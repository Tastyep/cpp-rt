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

  double intersect(std::array<double, 3> rayVec, Camera camera) const;

private:
  unsigned int radius = 0;
};

#endif /* end of include guard: RT_SPHERE_HH */
