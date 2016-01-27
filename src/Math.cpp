#include "Math.hh"

double Math::getPositiveMin(const auto &array) const {
  bool set = false;
  double smallest;

  for (const auto &elem : array) {
    if (elem > 0 && (set == false || elem < smallest)) {
      set = true;
      smallest = elem;
    }
  }
  return smallest;
}

double Math::solveSecond(const Vector &coefs,
                         std::array<double, 2> solutions) const {
  double delta;
  double sqrtDelta;

  if (coefs.x <= Math::eps && coefs.x >= Math::eps)
    return -1;
  delta = coefs.y * coefs.y - (4.0 * coefs.x * coefs.z);
  if (delta < 0)
    return -1;
  if (delta == 0)
    return (-coefs.y / (2.0 * coefs.x));
  sqrtDelta = std::sqrt(delta);
  solutions[0] = (-coefs.y + sqrtDelta) / (2.0 * coefs.x);
  solutions[1] = (-coefs.y - sqrtDelta) / (2.0 * coefs.x);
  return getPositiveMin(solutions);
}

double Math::getVectorNorme(const Vector& vec) {
    
}