#include "LightModel.hh"
#include "Math.hh"
#include "Color.hh"

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

double LightModel::checkInter(const Vector &lightVec, const Camera &camera) {
  double lightK;

  for (auto object : this->objects) {
    lightK = object->intersect(-lightVec, camera);

    if (lightK >= 0 && lightK < 0.999999)
      return lightK;
  }
  return -1;
}

bool LightModel::sumPhongValues(std::shared_ptr<Light> light,
                                const Position &impact, const Vector &normVec,
                                const Vector &rayVec, Vector &phongComp,
                                const LightParameters &objLight) {
  const auto &lightPos = light->getPosition();
  Camera newCam(lightPos);
  Vector lightVec;
  double lightK;
  Vector reflected;
  Vector currentPhong;
  double cosTheta;
  double cosOmega;

  lightVec.x = lightPos.x - impact.x;
  lightVec.y = lightPos.y - impact.y;
  lightVec.z = lightPos.z - impact.z;
  lightK = this->checkInter(lightVec, newCam);
  if (lightK >= 0 && lightK < 0.999999)
    return false;
  lightVec.makeUnit();
  cosTheta = std::max(lightVec.dot(normVec), 0.0);
  reflected = 2.0 * cosTheta * normVec - lightVec;
  cosOmega = std::max(reflected.dot(-rayVec), 0.0);
  currentPhong.x = objLight.Ia * 0;
  currentPhong.y =
      1.0 * objLight.Id * cosTheta; // change 1.0 by the intensity of the light
  currentPhong.z = 1.0 * objLight.Is * std::pow(cosOmega, 50);
  phongComp.x = std::max(phongComp.x, currentPhong.x);
  phongComp.y = std::max(phongComp.y, currentPhong.y);
  phongComp.z = std::max(phongComp.z, currentPhong.z);
  return true;
}

unsigned int LightModel::applyLights(std::shared_ptr<SceneObj> obj, double k,
                                     const Camera &camera, Vector rayVec) {
  Vector normVec;
  Vector phongComp = {0, 0, 0};
  Position impact;
  Color color = obj->getColor();
  Color specularColor = 0xFFFFFF;
  Color sumLightColor(0);
  unsigned int nbAppliedColor = 0;
  Math math;

  impact.x = camera.pos.x + k * rayVec.x;
  impact.y = camera.pos.y + k * rayVec.y;
  impact.z = camera.pos.z + k * rayVec.z;

  this->getDistanceAndNormal(normVec, camera, obj, rayVec, k);
  rayVec.makeUnit();
  normVec.makeUnit();
  for (auto light : this->lights) {
    if (this->sumPhongValues(light, impact, normVec, rayVec, phongComp,
                             obj->getLightParameters())) {
      ++nbAppliedColor;
      sumLightColor += Color(light->getColor());
    }
  }
  if (nbAppliedColor > 0)
    color.mix(sumLightColor / nbAppliedColor, 0.2);
  color *= phongComp.y;
  specularColor *= phongComp.z;
  color += specularColor;
  color.limit();
  return color.toInteger();
}