#include "Math.hh"

#include <cmath>

double Math::getPositiveMin(const auto &array) const {
  bool set = false;
  double smallest;

  for (const auto &elem : array) {
    if (elem > 0 && (set == false || elem < smallest)) {
      set = true;
      smallest = elem;
    }
  }
  return smallest;
}

double Math::solveSecond(const Vector &coefs,
                         std::array<double, 2> solutions) const {
  double delta;
  double sqrtDelta;

  if (coefs.x <= Math::eps && coefs.x >= Math::eps)
    return -1;
  delta = coefs.y * coefs.y - (4.0 * coefs.x * coefs.z);
  if (delta < 0)
    return -1;
  if (delta == 0)
    return (-coefs.y / (2.0 * coefs.x));
  sqrtDelta = std::sqrt(delta);
  solutions[0] = (-coefs.y + sqrtDelta) / (2.0 * coefs.x);
  solutions[1] = (-coefs.y - sqrtDelta) / (2.0 * coefs.x);
  return getPositiveMin(solutions);
}

Vector Math::calcReflectedVector(const Vector &ray,
                                 const Vector &normal) const {
  double cosAngle;

  cosAngle = ray.dot(normal);
  return (2.0 * cosAngle * normal - ray);
}

Vector Math::calcNormalVector(Position pos, std::shared_ptr<SceneObj> obj,
                              Vector rayVec, double k) const {
  Position impact;
  const Position &objPos = obj->getPosition();
  Vector normal;

  obj->applyTransformations(pos, rayVec);
  impact.x = pos.x + k * rayVec.x;
  impact.y = pos.y + k * rayVec.y;
  impact.z = pos.z + k * rayVec.z;
  obj->calcNormal(normal, impact);
  return normal;
}