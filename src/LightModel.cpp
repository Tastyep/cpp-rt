#include "LightModel.hh"
#include "Math.hh"

#include <cmath>
#include <iostream>

LightModel::LightModel(const std::vector<std::shared_ptr<Light>> &lights,
                       const std::vector<std::shared_ptr<SceneObj>> &objects)
    : lights(lights), objects(objects) {}

double LightModel::getDistanceAndNormal(Vector &normal, Camera camera,
                                        std::shared_ptr<SceneObj> obj,
                                        Vector rayVec, double k) {
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
                                     const Camera &camera, Vector rayVec) {
  Vector normVec;
  Vector lightVec;
  Vector phongComp = {0, 0, 0};
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
  for (const auto &light : this->lights) {
    const auto &lightPos = light->getPosition();
    Camera newCam(lightPos);
    double newK = 0;
    Vector reflected;
    Vector currentPhong;

    lightVec.x = lightPos.x - impact.x;
    lightVec.y = lightPos.y - impact.y;
    lightVec.z = lightPos.z - impact.z;
    for (auto object : this->objects) {
      newK = object->intersect(-lightVec, newCam);

      if (newK >= 0 && newK < 0.999999)
        break;
    }
    if (newK >= 0 && newK < 0.999999)
      continue;
    lightVec.makeUnit();
    cosTheta = std::max(lightVec.dot(normVec), 0.0);
    reflected = 2.0 * cosTheta * normVec - lightVec;
    cosOmega = std::max(reflected.dot(-rayVec), 0.0);
    currentPhong.x = objLight.Ia * 0;
    currentPhong.y = 1.0 * objLight.Id *
                     cosTheta; // change 1.0 by the intensity of the light
    currentPhong.z = 1.0 * objLight.Is * std::pow(cosOmega, 40);
    phongComp.x = std::max(phongComp.x, currentPhong.x);
    phongComp.y = std::max(phongComp.y, currentPhong.y);
    phongComp.z = std::max(phongComp.z, currentPhong.z);
  }
  color = math.multiplyColor(color, phongComp.y);
  specularColor = math.multiplyColor(0xFFFFFF, phongComp.z);
  color = math.addColor(color, specularColor);
  return color;
}