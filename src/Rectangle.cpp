#include "Rectangle.hh"
#include "Math.hh"

#include <iostream>

Rectangle::Rectangle() {
  IntegerValues = {{"color", color}};
  FloatingValues = {{"x", pos.x},       {"y", pos.y},     {"z", pos.z},
                    {"Ia", light.Ia},   {"Id", light.Id}, {"Is", light.Is},
                    {"height", height}, {"width", width}};
}

double Rectangle::intersect(Vector rayVec, Camera camera) const {
  Position vecPos = camera.pos;
  this->applyTransformations(vecPos, rayVec);
  Vector normal(-this->width, 0, this->height);
  Vector objPos(pos.x, pos.y, pos.z);
  Vector camPos(vecPos.x, vecPos.y, vecPos.z);
  Vector B(this->width, 0, this->height);
  double r, d, n;

  d = normal.scale(rayVec);
  n = normal.scale(objPos) - normal.scale(camPos);
  if (d == 0)
    return -1;
  r = n / d;
  if (r < 0)
    return -1;
  return r;
  Position inter;
  inter.x = vecPos.x + r * rayVec.x;
  inter.y = vecPos.y + r * rayVec.y;
  inter.z = vecPos.z + r * rayVec.z;
  Vector interVec(pos.x - inter.x, pos.y - inter.y, pos.z - inter.z);
  interVec.makeUnit();
  B.makeUnit();
  double p = interVec.scale(B);
  // std::cout << p << "\n";
  if (p >= -0.000001 && p <= 0.000001)
    return r;
  return -1;
}

void Rectangle::calcNormal(Vector &normVec, const Position &impact) const {
  normVec.x = -this->width;
  normVec.y = 0;
  normVec.z = this->height;
}