#include "Rt.hh"

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
    if (k > Math::zero && (k < kmin || kmin == -1)) {
      kmin = k;
      savedObj = object;
    }
  }
  return {savedObj, kmin};
}

Color Rt::getReflectedColor(const InterData &origRay, InterData ray, int pass) {
  Vector reflected;
  std::pair<std::shared_ptr<SceneObj>, double> reflectedObj;

  // ray.ray = ray.impact - ray.vecPos;
  reflected = this->math.calcReflectedVector(ray.ray, ray.normal);
  reflectedObj = this->getClosestObj(reflected, Camera(ray.impact));
  if (reflectedObj.second < Math::zero)
    return Color(0x000000);
  ray.obj = reflectedObj.first;
  ray.k = reflectedObj.second;
  ray.ray = reflected;
  ray.vecPos = ray.impact;
  return this->ComputeObjectColor(origRay, ray, pass);
}

Color Rt::getRefractedColor(const InterData &origRay, InterData ray, int pass) {
  std::pair<std::shared_ptr<SceneObj>, double> refractedObj;

  refractedObj = this->getClosestObj(ray.ray, Camera(ray.impact));
  if (refractedObj.first == nullptr)
    return Color(0x000000);
  ray.obj = refractedObj.first;
  ray.k = refractedObj.second;
  ray.vecPos = ray.impact;
  return this->ComputeObjectColor(origRay, ray, pass);
}

Color Rt::ComputeObjectColor(const InterData &origRay, InterData ray,
                             int pass) {
  Color reflectedColor(0);
  Color refractedColor(0);
  Color cuColor(ray.obj->getColor());
  float reflecIdx = ray.obj->getReflectionIndex();
  float refracIdx = ray.obj->getTransparencyIndex();

  ++pass;
  if (pass > 1) { // Means there is at least one recursion and we are not
                  // computing it again
    ray.calcImpact();
    ray.normal = this->math.calcNormalVector(ray.vecPos, ray.obj, ray.ray,
                                             ray.k, ray.impact);
  }
  if (pass > 10) {
    return ray.obj->getColor(); // apply light
  }
  if (reflecIdx > Math::zero) {
    reflectedColor = getReflectedColor(origRay, ray, pass);
  }
  if (refracIdx > Math::zero) {
    refractedColor = getRefractedColor(origRay, ray, pass);
  }
  cuColor = this->lightModel.applyLights(ray.obj, cuColor, ray.k,
                                         Camera(ray.vecPos), ray.ray);
  if (reflecIdx > Math::zero || refracIdx > Math::zero) {
    if (reflecIdx > Math::zero && refracIdx > Math::zero) {
      // Handle later
      std::cout << "Not handled" << "\n";
    } else if (reflecIdx > Math::zero) {
      cuColor.mix(reflectedColor, reflecIdx);
    } else
      cuColor.mix(refractedColor, refracIdx);
  }
  return cuColor;
}

unsigned int Rt::computePixelColor(const Vector &rayVec) {
  Color color(0);
  auto pair = this->getClosestObj(rayVec, this->camera);
  InterData interData(rayVec, this->camera.pos, pair.first, pair.second);

  if (interData.obj == nullptr) // No object found
    return color.toInteger();

  interData.calcImpact();
  interData.normal =
      this->math.calcNormalVector(interData.vecPos, interData.obj,
                                  interData.ray, interData.k, interData.impact);
  color = this->ComputeObjectColor(interData, interData, 0);
  return color.toInteger();
}