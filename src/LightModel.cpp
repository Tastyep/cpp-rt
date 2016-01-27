#include "LightModel.hh"
#include "Math.hh"

#include <cmath>
#include <iostream>

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
                                     Vector rayVec) {
  Vector normVec;
  Vector lightVec;
  Vector phongComp;
  Position impact;
  LightParameters objLight = obj->getLightParameters();
  unsigned int color = obj->getColor();
  unsigned int specularColor = 0xFFFFFF;
  double cosTheta;
  double cosOmega;
  Math math;
  
  impact.x = camera.pos.x + k * rayVec.x;
  impact.y = camera.pos.y + k * rayVec.y;
  impact.z = camera.pos.z + k * rayVec.z;

  this->getDistanceAndNormal(normVec, camera, obj, rayVec, k);
  rayVec.makeUnit();
  normVec.makeUnit();
  for (const auto& light: this->lights) {
      const auto& lightPos = light->getPosition();
      Vector reflected;
  
      lightVec.x = lightPos.x - impact.x;
      lightVec.y = lightPos.y - impact.y;
      lightVec.z = lightPos.z - impact.z;
      lightVec.makeUnit();
      cosTheta = std::max(lightVec.dot(normVec), 0.0);
      reflected = 2.0 * cosTheta * normVec - lightVec;
      cosOmega = std::max(reflected.dot(-rayVec), 0.0);
      phongComp.x = objLight.Ia * 0;
      phongComp.y = 1.0 * objLight.Id * cosTheta;// change 1.0 by the intensity of the light
      phongComp.z = 1.0 * objLight.Is * std::pow(cosOmega, 30);
      color = math.multiplyColor(color, phongComp.y);
      specularColor = math.multiplyColor(specularColor, phongComp.z);
      color = math.addColor(color, specularColor);
  }
  return color;
}