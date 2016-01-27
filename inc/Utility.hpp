#ifndef RT_UTILITY_HPP
#define RT_UTILITY_HPP

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
};

#endif /* end of include guard: RT_UTILITY_HPP */
