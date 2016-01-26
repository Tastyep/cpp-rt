#ifndef RT_RT_HH
#define RT_RT_HH

#include "Camera.hh"
#include "SceneObj.hh"
#include "LightModel.hh"

#include <memory>
#include <utility>
#include <SFML/System.hpp>

class Rt {
public:
  Rt(const Camera &camera,
     const std::vector<std::shared_ptr<SceneObj>> &objects,
     const std::vector<std::shared_ptr<Light>> &lights);

  ~Rt() = default;
  Rt(const Rt &other) = default;
  Rt(Rt &&other) = default;
  Rt &operator=(const Rt &other) = default;
  Rt &operator=(Rt &&other) = default;

  unsigned int computePixelColor(const std::array<double, 3>& rayVec);
  void computeRayVec(std::array<double, 3>& rayVec, int x, int y, sf::Vector2i screenSize) const;

private:
  std::pair<std::shared_ptr<SceneObj>, double> getClosestObj(const auto& rayVec);

private:
  static constexpr unsigned int Dist = 1000;

private:
  const Camera &camera;
  const std::vector<std::shared_ptr<SceneObj>> &objects;
  LightModel lightModel;
};

#endif /* end of include guard: RT_RT_HH */
