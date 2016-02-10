#include "Sphere.hh"
#include "Math.hh"

#include <iostream>

Sphere::Sphere() {
  IntegerValues = {{"radius", radius}, {"color", color}};
  FloatingValues = {{"x", pos.x},     {"y", pos.y},     {"z", pos.z},
                    {"Ia", light.Ia}, {"Id", light.Id}, {"Is", light.Is}, {"Reflection", reflection}};
}

double Sphere::intersect(Vector rayVec, Camera camera) const {
  Position vecPos = camera.pos;
  this->applyTransformations(vecPos, rayVec);
  Vector coef;
  std::array<double, 2> solutions;
  double solution;
  Math math;

  coef.x = rayVec.x * rayVec.x + rayVec.y * rayVec.y + rayVec.z * rayVec.z;
  coef.y =
      2.0 * (vecPos.x * rayVec.x + vecPos.y * rayVec.y + vecPos.z * rayVec.z);
  coef.z = vecPos.x * vecPos.x + vecPos.y * vecPos.y + vecPos.z * vecPos.z -
           this->radius * this->radius;
  solution = math.solveSecond(coef, solutions);
  return solution;
}

void Sphere::calcNormal(Vector &normVec, const Position &impact) const {
  normVec.x = impact.x - pos.x;
  normVec.y = impact.y - pos.y;
  normVec.z = impact.z - pos.z;
  normVec.makeUnit();
}
