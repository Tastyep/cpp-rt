#include "LightModel.hh"
#include "Color.hh"
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
  Position camPos = camera.pos;

  impact.x = camPos.x + k * rayVec.x;
  impact.y = camPos.y + k * rayVec.y;
  impact.z = camPos.z + k * rayVec.z;
  obj->calcNormal(normal, impact);
  distCoef.x = camPos.x - impact.x;
  distCoef.y = camPos.y - impact.y;
  distCoef.z = camPos.z - impact.z;
  distance = std::sqrt(distCoef.x * distCoef.x + distCoef.y * distCoef.y +
                       distCoef.z * distCoef.z);
  return distance;
}

std::pair<std::shared_ptr<SceneObj>, double>
LightModel::checkInter(const Vector &lightVec, const Camera &camera) {
  double lightK;

  for (auto object : this->objects) {
    lightK = object->intersect(-lightVec, camera);

    if (lightK > Math::zero && lightK < 0.9999999)
      return {object, lightK};
  }
  return {nullptr, -1};
}

bool LightModel::sumPhongValues(std::shared_ptr<Light> light,
                                const Position &impact, const Vector &normVec,
                                const Vector &rayVec, Vector &phongComp,
                                const LightParameters &objLight) {
  const auto &lightPos = light->getPosition();
  Camera newCam(lightPos);
  Vector lightVec;
  Vector reflected;
  Vector currentPhong;
  double cosTheta;
  double cosOmega;
  double ratio = 1.0;

  lightVec.x = lightPos.x - impact.x;
  lightVec.y = lightPos.y - impact.y;
  lightVec.z = lightPos.z - impact.z;
  auto objPair = this->checkInter(lightVec, newCam);
  if (objPair.first) {
    ratio = objPair.first->getTransparencyIndex(); // the more Transparent, the
                                                   // more light goes through
    if (ratio == 0)
      return false;
  }
  lightVec.makeUnit();
  cosTheta = std::max(lightVec.dot(normVec), 0.0);
  reflected = lightVec - 2.0 * cosTheta * normVec;
  cosOmega = std::max(reflected.dot(rayVec), 0.0);
  currentPhong.x = objLight.Ia * 0 * ratio;
  currentPhong.y = 1.0 * objLight.Id * cosTheta *
                   ratio; // change 1.0 by the intensity of the light
  currentPhong.z = 1.0 * objLight.Is * std::pow(cosOmega, 80) * ratio;
  phongComp.x = std::max(phongComp.x, currentPhong.x);
  phongComp.y = std::max(phongComp.y, currentPhong.y);
  phongComp.z = std::max(phongComp.z, currentPhong.z);
  return true;
}

Color LightModel::applyLights(std::shared_ptr<SceneObj> obj, Color color,
                              double k, const Camera &camera, Vector rayVec) {
  Vector normVec;
  Vector phongComp = {0, 0, 0};
  Position impact;
  Color specularColor = 0xFFFFFF;
  Color sumLightColor(0);
  unsigned int nbAppliedColor = 0;
  Math math;

  impact.x = camera.pos.x + k * rayVec.x;
  impact.y = camera.pos.y + k * rayVec.y;
  impact.z = camera.pos.z + k * rayVec.z;

  this->getDistanceAndNormal(normVec, camera, obj, rayVec, k);
  rayVec.makeUnit();
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
  return color;
}