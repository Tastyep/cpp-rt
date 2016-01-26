#include "Rt.hh"

#include <iostream>

Rt::Rt(const Camera &camera,
       const std::vector<std::shared_ptr<SceneObj>> &objects)
    : camera(camera), objects(objects) {}

void Rt::computeRayVec(std::array<double, 3> &rayVec, int x,
                       int y, sf::Vector2i screenSize) const {
  rayVec[0] = Rt::Dist - camera.pos.x;
  rayVec[1] = (screenSize.x / 2 - x) - camera.pos.y;
  rayVec[2] = (screenSize.y / 2 - y) - camera.pos.z;
  // Apply rotation
}

std::shared_ptr<SceneObj> Rt::getClosestObj(const auto &rayVec) {
  double k;
  double kmin = -1;
  std::shared_ptr<SceneObj> savedObj = nullptr;

  for (const auto &object : this->objects) {
    k = object->intersect(rayVec, this->camera);
    if (k > 0 && (k < kmin || kmin == -1)) {
      kmin == k;
      savedObj = object;
    }
  }
  return savedObj;
}

unsigned int Rt::computePixelColor(const std::array<double, 3> &rayVec) {
  std::shared_ptr<SceneObj> closestObj = this->getClosestObj(rayVec);
  unsigned int color;

  if (closestObj == nullptr)
    return 0xFFFFFF;
  color = closestObj->getColor();
  return color;
}