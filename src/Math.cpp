#include "Math.hh"

#include <cmath>

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

unsigned int Math::multiplyColor(unsigned int color, const Vector& vec) const {
    unsigned int r = (color >> 16) & 0xFF;
    unsigned int g = (color >> 8) & 0xFF;
    unsigned int b = color & 0xFF;
    unsigned int newColor = 0;
    
    r *= vec.x;
    g *= vec.y;
    b *= vec.z;
    if (r > 255)
        r = 255;
    if (g > 255)
        g = 255;
    if (b > 255)
        b = 255;
    newColor = r << 16;
    newColor |= g << 8;
    newColor |= b;
    return newColor;
}

unsigned int Math::multiplyColor(unsigned int color, double value) const {
    unsigned int r = (color >> 16) & 0xFF;
    unsigned int g = (color >> 8) & 0xFF;
    unsigned int b = color & 0xFF;
    unsigned int newColor = 0;
    
    r = static_cast<double>(r) * value;
    g = static_cast<double>(g) * value;
    b = static_cast<double>(b) * value;
    if (r > 255)
        r = 255;
    if (g > 255)
        g = 255;
    if (b > 255)
        b = 255;
    newColor = r << 16;
    newColor |= g << 8;
    newColor |= b;
    return newColor;
}

unsigned int Math::addColor(unsigned int color, unsigned int color2) const {
    unsigned int r1 = (color >> 16) & 0xFF;
    unsigned int g1 = (color >> 8) & 0xFF;
    unsigned int b1 = color & 0xFF;
    unsigned int r2 = (color2 >> 16) & 0xFF;
    unsigned int g2 = (color2 >> 8) & 0xFF;
    unsigned int b2 = color2 & 0xFF;
    unsigned int newColor = 0;
    
    r1 += r2;
    g1 += g2;
    b1 += b2;
    if (r1 > 255)
        r1 = 255;
    if (g1 > 255)
        g1 = 255;
    if (b1 > 255)
        b1 = 255;
    newColor = r1 << 16;
    newColor |= g1 << 8;
    newColor |= b1;
    return newColor;
}