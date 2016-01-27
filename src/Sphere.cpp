#include "Sphere.hh"
#include "Math.hh"

#include <iostream>

Sphere::Sphere() {
  IntegerValues = {{"radius", radius}, {"color", color}};
  FloatingValues = {{"x", pos.x},     {"y", pos.y},     {"z", pos.z},
                    {"Ia", light.Ia}, {"Id", light.Id}, {"Is", light.Is}};
}

double Sphere::intersect(Vector rayVec, Camera camera) const {
  this->applyTransformations(camera, rayVec);
  Vector coef;
  std::array<double, 2> solutions;
  double solution;
  Math math;

  coef.x = rayVec.x * rayVec.x + rayVec.y * rayVec.y + rayVec.z * rayVec.z;
  coef.y = 2.0 * (camera.pos.x * rayVec.x + camera.pos.y * rayVec.y +
                  camera.pos.z * rayVec.z);
  coef.z = camera.pos.x * camera.pos.x + camera.pos.y * camera.pos.y +
           camera.pos.z * camera.pos.z - this->radius * this->radius;
  solution = math.solveSecond(coef, solutions);
  return solution;
}

void Sphere::calcNormal(Vector &normVec, const Position &impact) const {
  normVec.x = impact.x;
  normVec.y = impact.y;
  normVec.z = impact.z;
}
