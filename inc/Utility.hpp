#ifndef RT_UTILITY_HPP
#define RT_UTILITY_HPP

#include <cmath>

struct Position {
  double x;
  double y;
  double z;

  Position(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

struct Vector {
  double x;
  double y;
  double z;

  Vector(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

  double getVectorNorme() { return std::sqrt(x * x + y * y + z * z); }

  void makeUnit() {
    double norme = getVectorNorme();

    if (norme == 0)
      norme = 0.0000001;
    x /= norme;
    y /= norme;
    z /= norme;
  }

  double scale(const Vector &vec) {
    return (x * vec.x + y * vec.y + z * vec.z);
  }

  double dot(const Vector &vec) {
    double norme = getVectorNorme();

    if (norme == 0)
      norme = 0.0000001;
    return scale(vec) / norme;
  }

  Vector operator+(const Vector &vec) const {
    return {x + vec.x, y + vec.y, z + vec.z};
  }

  Vector operator-(const Vector &vec) const {
    return {x - vec.x, y - vec.y, z - vec.z};
  }
  
  Vector operator-() const {
    return {-x, -y, -z};
  }

  Vector operator*(const Vector &vec) const {
    return {x * vec.x, y * vec.y, z * vec.z};
  }

  Vector operator*(double value) const {
    return {x * value, y * value, z * value};
  }
};

inline Vector operator*(double value, const Vector &vec) { return vec * value; }

#endif /* end of include guard: RT_UTILITY_HPP */
