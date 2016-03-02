#ifndef RT_VECTOR_HH
#define RT_VECTOR_HH

struct Position;

struct Vector {
  double x;
  double y;
  double z;

  Vector(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
  Vector(Position pos);

  double getVectorNorme() const { return std::sqrt(x * x + y * y + z * z); }

  void makeUnit() {
    double norme = getVectorNorme();

    if (norme == 0)
      norme = 0.0000001;
    this->x /= norme;
    this->y /= norme;
    this->z /= norme;
  }

  double dot(const Vector &vec) const {
    return (x * vec.x + y * vec.y + z * vec.z);
  }

  Vector operator+(const Vector &vec) const {
    return {x + vec.x, y + vec.y, z + vec.z};
  }

  Vector operator+(const Position &pos) const {
    return {x + pos.x, y + pos.y, z + pos.z};
  }

  Vector operator-(const Vector &vec) const {
    return {x - vec.x, y - vec.y, z - vec.z};
  }

  Vector operator-() const { return {-x, -y, -z}; }

  Vector operator*(const Vector &vec) const {
    return {x * vec.x, y * vec.y, z * vec.z};
  }

  Vector operator*(double value) const {
    return {x * value, y * value, z * value};
  }
};

inline std::ostream &operator<<(std::ostream &os, const Vector &vec) {
  os << "[" << vec.x << "," << vec.y << "," << vec.z << "]";
  return os;
}

inline Vector operator*(double value, const Vector &vec) { return vec * value; }

#endif /* end of include guard: RT_VECTOR_HH */
