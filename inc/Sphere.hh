#ifndef RT_SPHERE_HH
#define RT_SPHERE_HH

#include "Objects.hpp"

#include <vector>

class Sphere : public Objects {
public:
  Sphere();

  ~Sphere() = default;
  Sphere(const Sphere &other) = default;
  Sphere(Sphere &&other) = default;
  Sphere &operator=(const Sphere &other) = default;
  Sphere &operator=(Sphere &&other) = default;

  bool intersect() const;
  bool parseArgs(std::stringstream &ss);

private:
    bool parseArg(const std::vector<std::string>& tokens);

private:
  std::map<std::string, std::reference_wrapper<unsigned int>> IntegerValues;
  std::map<std::string, std::reference_wrapper<double>> FloatingValues;
  unsigned int radius = 0;
  unsigned int color = 0;
  position pos;
};

#endif /* end of include guard: RT_SPHERE_HH */
