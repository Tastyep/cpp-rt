#include "Rectangle.hh"
#include "Math.hh"

#include <iostream>

Rectangle::Rectangle() {
  IntegerValues = {{"color", color}};
  FloatingValues = {
      {"x", pos.x},        {"y", pos.y},     {"z", pos.z},
      {"Ia", light.Ia},    {"Id", light.Id}, {"Is", light.Is},
      {"height", height},  {"width", width}, {"Reflection", reflection},
      {"Bumping", bumping}};
}

double Rectangle::intersect(Vector rayVec, Camera camera) const {
  Position vecPos = camera.pos;
  this->applyTransformations(vecPos, rayVec);
  Vector normal(-this->width, 0, this->height);
  Vector objPos(pos.x, pos.y, pos.z);
  Vector camPos(vecPos.x, vecPos.y, vecPos.z);
  Vector B(this->width, 0, this->height);
  double r, d, n;

  d = normal.dot(rayVec);
  n = normal.dot(objPos) - normal.dot(camPos);
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
  double p = interVec.dot(B);
  // std::cout << p << "\n";
  if (p >= -0.000001 && p <= 0.000001)
    return r;
  return -1;
}

void Rectangle::calcNormal(Vector &normVec, const Position &impact) const {
  normVec.x = -this->width;
  normVec.y = 0;
  normVec.z = this->height;

  if (this->bumping > 0) {
    //   float fbm(float x, float y, int octaves = 2, float scale = 1,
    //             float lacunarity = 1, float gain = 0.5) const;
    float coefx = noise.fbm(impact.x, impact.y, impact.z, 1, 0.2);
    float coefy = noise.fbm(impact.y, impact.z, impact.x, 1, 0.2);
    float coefz = noise.fbm(impact.z, impact.x, impact.y, 1, 0.2);

    normVec.x =
        (1.0 - this->bumping) * normVec.x + this->bumping * coefx * normVec.x;
    normVec.y =
        (1.0 - this->bumping) * normVec.y + this->bumping * coefy * normVec.y;
    normVec.z =
        (1.0 - this->bumping) * normVec.z + this->bumping * coefz * normVec.z;
  }
  normVec.makeUnit();
}