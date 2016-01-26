#include "Math.hh"

double Math::getPositiveMin(const auto &array) const {
  bool set = false;
  double smallest;

  for (const auto &elem : array) {
    if (elem > 0 && (set == false || elem < smallest))
      smallest = elem;
  }
  return smallest;
}

double Math::solveSecond(const std::array<double, 3> &coefs,
                         std::array<double, 2> solutions) const {
  double delta;
  double sqrtDelta;

  if (coefs[0] == 0)
    return -1;
  delta = coefs[1] * coefs[1] - (4.0 * coefs[0] * coefs[2]);
  if (delta < 0)
    return -1;
  if (delta == 0)
    return (-coefs[1] / (2.0 * coefs[0]));
  sqrtDelta = std::sqrt(delta);
  solutions[0] = (-coefs[1] + sqrtDelta) / (2.0 * coefs[0]);
  solutions[1] = (-coefs[1] - sqrtDelta) / (2.0 * coefs[0]);
  return getPositiveMin(solutions);
}