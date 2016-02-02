#ifndef RT_MATH_HH
#define RT_MATH_HH

#include "Utility.hpp"
#include "SceneObj.hh"

#include <array>
#include <memory>

class Math {
public:
  static double constexpr eps = 0.000001;

public:
  Math() = default;

  ~Math() = default;
  Math(const Math &other) = default;
  Math(Math &&other) = default;
  Math &operator=(const Math &other) = default;
  Math &operator=(Math &&other) = default;

  double solveSecond(const Vector &coefs,
                     std::array<double, 2> solutions) const;
  Vector calcReflectedVector(const Vector &ray, const Vector &normal) const;
  Vector calcNormalVector(Position camera, std::shared_ptr<SceneObj> obj,
                          Vector rayVec, double k) const;

private:
  double getPositiveMin(const auto &array) const;
};

#endif /* end of include guard: RT_MATH_HH */
