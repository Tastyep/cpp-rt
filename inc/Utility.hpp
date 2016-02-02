#ifndef RT_UTILITY_HPP
#define RT_UTILITY_HPP

#include <cmath>

struct Position;

struct Vector {
  double x;
  double y;
  double z;

  Vector(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

  double getVectorNorme() const { return std::sqrt(x * x + y * y + z * z); }

  void makeUnit() {
    double norme = getVectorNorme();

    if (norme == 0)
      norme = 0.0000001;
    this->x /= norme;
    this->y /= norme;
    this->z /= norme;
  }

  double scale(const Vector &vec) const {
    return (x * vec.x + y * vec.y + z * vec.z);
  }

  double dot(const Vector &vec) const {
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

struct Position {
  double x;
  double y;
  double z;

  Position(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
  
  double distance(const Position& pos) const {
      double dx = pos.x - x;
      double dy = pos.y - y;
      double dz = pos.z - z;
      return std::sqrt(dx * dx + dy * dy + dz * dz);
  }
  
  Vector operator-(const Position& p) const {
      return Vector(x - p.x, y - p.y, z - p.z);
  }
};

inline Vector operator*(double value, const Vector &vec) { return vec * value; }

#endif /* end of include guard: RT_UTILITY_HPP */
