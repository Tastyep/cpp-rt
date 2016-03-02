#ifndef RT_RT_HH
#define RT_RT_HH

#include "Camera.hh"
#include "LightModel.hh"
#include "Math.hh"
#include "SceneObj.hh"

#include <SFML/System.hpp>
#include <memory>
#include <utility>

struct InterData {
  Vector ray;
  Vector normal;
  Position vecPos;
  Position impact;
  double k;
  std::shared_ptr<SceneObj> obj;
  InterData(const Vector &ray, const Position &pos,
            std::shared_ptr<SceneObj> obj, double k)
      : ray(ray), vecPos(pos), obj(obj), k(k) {}

  void calcImpact() {
    impact.x = vecPos.x + k * ray.x;
    impact.y = vecPos.y + k * ray.y;
    impact.z = vecPos.z + k * ray.z;
  }
};

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

  unsigned int computePixelColor(const Vector &rayVec);
  void computeRayVec(Vector &rayVec, int x, int y,
                     sf::Vector2i screenSize) const;

private:
  std::pair<std::shared_ptr<SceneObj>, double>
  getClosestObj(const auto &rayVec, const Camera &camera);
  Color ComputeObjectColor(const InterData &origRay, InterData ray, int pass);
  Color getReflectedColor(const InterData &origRay, InterData ray, int pass);
  Color getRefractedColor(const InterData &origRay, InterData ray, int pass);

private:
  static constexpr unsigned int Dist = 1000;

private:
  const Camera &camera;
  const std::vector<std::shared_ptr<SceneObj>> &objects;
  LightModel lightModel;
  Math math;
};

#endif /* end of include guard: RT_RT_HH */
