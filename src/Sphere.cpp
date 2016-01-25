#include "Sphere.hh"

#include <iostream>

Sphere::Sphere() {
  IntegerValues = {{"radius", radius}, {"color", color}};
  FloatingValues = {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}};
}

double Sphere::intersect(const std::array<double, 3>& rayVec, const Camera& camera) const {
}

