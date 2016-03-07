#include "Sphere.hh"
#include "Math.hh"

#include <iostream>

Sphere::Sphere() {
  IntegerValues = {{"radius", radius}, {"color", color}};
  FloatingValues = {{"x", pos.x},
                    {"y", pos.y},
                    {"z", pos.z},
                    {"Ia", light.Ia},
                    {"Id", light.Id},
                    {"Is", light.Is},
                    {"Reflection", reflection},
                    {"Transparency", alpha},
                    {"Absorbance", absorbance},
                    {"Bumping", bumping}};
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
