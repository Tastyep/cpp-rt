#include "Sphere.hh"
#include "Math.hh"

#include <iostream>

Sphere::Sphere() {
  IntegerValues = {{"radius", radius}, {"color", color}};
  FloatingValues = {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}};
}

double Sphere::intersect(std::array<double, 3> rayVec, Camera camera) const {
  this->apply_transformations(camera, rayVec);
  std::array<double, 3> coef;
  std::array<double, 2> solutions;
  double solution;
  Math math;

  coef[0] =
      rayVec[0] * rayVec[0] + rayVec[1] * rayVec[1] + rayVec[2] * rayVec[2];
  coef[1] = 2.0 * (camera.pos.x * rayVec[0] + camera.pos.y * rayVec[1] +
                   camera.pos.z * rayVec[2]);
  coef[2] = camera.pos.x * camera.pos.x + camera.pos.y * camera.pos.y +
            camera.pos.z * camera.pos.z - this->radius * this->radius;
  solution = math.solveSecond(coef, solutions);
  return solution;
}
