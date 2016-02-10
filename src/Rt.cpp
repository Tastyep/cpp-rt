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
    k = object->intersect(rayVec, camera);
    if (k > 0.000001 && (k < kmin || kmin == -1)) {
      kmin = k;
      savedObj = object;
    }
  }
  return {savedObj, kmin};
}
int toto = 0;
Color Rt::getReflectedColor(std::shared_ptr<SceneObj> obj, Camera camera,
                            Vector rayVec, const InterData& interData, double k,
                            unsigned int pass) {
  Color cuColor(obj->getColor());

  if (pass > 10)
    return cuColor;
  if (obj->getReflectionIndex() == 0) {
    cuColor = lightModel.applyLights(obj, cuColor, interData.k, interData.pos, interData.ray);
    return cuColor;
  }

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

  reflectedObj = this->getClosestObj(reflected, Camera(impact));
  if (reflectedObj.second <= 0.000000) {
    cuColor.mix(0x000000, obj->getReflectionIndex());
    return cuColor;
  }
  newColor =
      this->getReflectedColor(reflectedObj.first, Camera(impact), reflected,
                              interData, reflectedObj.second, pass + 1);
  cuColor.mix(newColor, obj->getReflectionIndex());
  return cuColor;
}

unsigned int Rt::computePixelColor(const Vector &rayVec) {
  Color color(0);
  auto pair = this->getClosestObj(rayVec, this->camera);
  InterData interData(rayVec, this->camera.pos, pair.first, pair.second);

  if (interData.obj == nullptr)
    return color.toInteger();
  if (interData.obj->getReflectionIndex() > 0)
    color =
        getReflectedColor(interData.obj, this->camera, rayVec, interData, pair.second, 1);
  else
    color = interData.obj->getColor();
  color = lightModel.applyLights(interData.obj, color, interData.k, this->camera,
                                 rayVec);
  return color.toInteger();
}