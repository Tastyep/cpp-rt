#include "Sphere.hh"

Sphere::Sphere() {
  IntegerValues = {{"radius", radius}, {"color", color}};
  FloatingValues = {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}};
}

bool Sphere::intersect() const {}

