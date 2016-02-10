#include "Rt.hh"
#include "Math.hh"

#include <iostream>

Rt::Rt(const Camera &camera,
       const std::vector<std::shared_ptr<SceneObj>> &objects,
       const std::vector<std::shared_ptr<Light>> &lights)
    : camera(camera), objects(objects), lightModel(lights, objects) {}

void Rt::computeRayVec(Vector &rayVec, int x, int y,
                       sf::Vector2i screenSize) const {
  rayVec.x = Rt::Dist - camera.pos.x;
  rayVec.y = (screenSize.x / 2 - x) - camera.pos.y;
  rayVec.z = (screenSize.y / 2 - y) - camera.pos.z;
  // Apply rotation
}

std::pair<std::shared_ptr<SceneObj>, double>
Rt::getClosestObj(const auto &rayVec, const Camera &camera) {
  double k;
  double kmin = -1;
  std::shared_ptr<SceneObj> savedObj = nullptr;

  for (const auto &object : this->objects) {
    k = object->intersect(rayVec, this->camera);
    if (k > 0 && (k < kmin || kmin == -1)) {
      kmin = k;
      savedObj = object;
    }
  }
  return {savedObj, kmin};
}
int toto = 0;
Color Rt::getReflectedColor(std::shared_ptr<SceneObj> obj, Camera camera,
                            Vector rayVec, double k, unsigned int pass) {
  if (pass > 10)
    return obj->getColor();
  if (obj->getReflectionIndex() == 0) {
    // apply effects
    return obj->getColor();
  }

  Color cuColor(obj->getColor());
  Color newColor(0);
  Math math;
  Vector view;
  Vector normal;
  Vector reflected;
  Position impact;
  std::pair<std::shared_ptr<SceneObj>, double> reflectedObj;

  normal = math.calcNormalVector(camera.pos, obj, rayVec, k, impact);
  view = Vector(impact.x, impact.y, impact.z) -
         Vector(camera.pos.x, camera.pos.y, camera.pos.z);
  reflected = math.calcReflectedVector(view, normal);
  newColor.r = reflected.x * 127.0 + 127.0;
  newColor.g = reflected.y * 127.0 + 127.0;
  newColor.b = reflected.z * 127.0 + 127.0;
  return newColor;
  // std::cout << reflected << "\n";
  reflectedObj = this->getClosestObj(reflected, Camera(impact));
  if (reflectedObj.second <= 0) {
    cuColor.mix(0x000000, obj->getReflectionIndex());
    return cuColor;
  }
  newColor = this->getReflectedColor(reflectedObj.first, Camera(impact),
                                     reflected, reflectedObj.second, pass + 1);
  // apply effects
  cuColor.mix(newColor, obj->getReflectionIndex());
  return newColor;
}

unsigned int Rt::computePixelColor(const Vector &rayVec) {
  Color color(0);
  std::shared_ptr<SceneObj> obj;
  auto pair = this->getClosestObj(rayVec, this->camera);

  if (pair.first == nullptr)
    return color.toInteger();
  obj = pair.first;
  if (obj->getReflectionIndex() > 0)
    color = getReflectedColor(obj, this->camera, rayVec, pair.second, 1);
  else
    color = obj->getColor();
  color = lightModel.applyLights(pair.first, color, pair.second, this->camera,
                                 rayVec);
  return color.toInteger();
}