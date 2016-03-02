#ifndef RT_POSITION_HH
#define RT_POSITION_HH

#include <cmath>

struct Vector;

struct Position {
  double x;
  double y;
  double z;

  Position(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

  Position &operator=(const Position &pos) {
    x = pos.x;
    y = pos.y;
    z = pos.z;
    return *this;
  }

  double distance(const Position &pos) const {
    double dx = pos.x - x;
    double dy = pos.y - y;
    double dz = pos.z - z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }

  Vector operator-(const Position &p) const {
    return Vector(x - p.x, y - p.y, z - p.z);
  }
};

#endif /* end of include guard: RT_POSITION_HH */
