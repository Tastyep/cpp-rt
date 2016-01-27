#ifndef RT_LIGHTMODEL_HH
#define RT_LIGHTMODEL_HH

#include "Light.hh"
#include "SceneObj.hh"
#include "Camera.hh"

#include <vector>
#include <array>
#include <memory>

class LightModel {
public:
  LightModel(const std::vector<std::shared_ptr<Light>> &lights);

  ~LightModel() = default;
  LightModel(const LightModel &other) = default;
  LightModel(LightModel &&other) = default;
  LightModel &operator=(const LightModel &other) = default;
  LightModel &operator=(LightModel &&other) = default;

  unsigned int applyLights(std::shared_ptr<SceneObj> obj, double k,
                           const Camera &camera,
                           Vector rayVec);

private:
  double getDistanceAndNormal(Vector &normal, Camera camera,
                              std::shared_ptr<SceneObj> obj,
                              Vector rayVec,
                              double k);

private:
  const std::vector<std::shared_ptr<Light>> &lights;
};

#endif /* end of include guard: RT_LIGHTMODEL_HH */
