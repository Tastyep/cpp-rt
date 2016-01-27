#include "LightModel.hh"

#include <cmath>

LightModel::LightModel(const std::vector<std::shared_ptr<Light>> &lights)
    : lights(lights) {}

double LightModel::getDistanceAndNormal(Vector &normal,
                                        Camera camera,
                                        std::shared_ptr<SceneObj> obj,
                                        Vector rayVec,
                                        double k) {
  Position impact;
  const Position &objPos = obj->getPosition();
  Position distCoef;
  double distance;
  
  obj->applyTransformations(camera, rayVec);
  impact.x = camera.pos.x + k * rayVec.x;
  impact.y = camera.pos.y + k * rayVec.y;
  impact.z = camera.pos.z + k * rayVec.z;
  obj->calcNormal(normal, impact);
  //  obj->applyInverseTransformation(camera, rayVec);
  impact.x += objPos.x;
  impact.y += objPos.y;
  impact.z += objPos.z;
  distCoef.x = camera.pos.x - impact.x;
  distCoef.y = camera.pos.y - impact.y;
  distCoef.z = camera.pos.z - impact.z;
  distance = std::sqrt(distCoef.x * distCoef.x + distCoef.y * distCoef.y +
                  distCoef.z * distCoef.z);
  return distance;
}

unsigned int LightModel::applyLights(std::shared_ptr<SceneObj> obj, double k,
                                     const Camera &camera,
                                     const Vector &rayVec) {
  Vector normVec;
  Vector lightVec;
  Position impact;
  
  impact.x = camera.pos.x + k * rayVec.x;
  impact.y = camera.pos.y + k * rayVec.y;
  impact.z = camera.pos.z + k * rayVec.z;

  this->getDistanceAndNormal(normVec, camera, obj, rayVec, k);
  for (const auto& light: this->lights) {
      const auto& lightPos = light->getPosition();
      
      lightVec.x = impact.x - lightPos.x;
      lightVec.y = impact.y - lightPos.y;
      lightVec.z = impact.z - lightPos.z;
  }
  return obj->getColor();
}