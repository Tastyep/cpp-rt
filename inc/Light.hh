#ifndef RT_LIGHT_HH
#define RT_LIGHT_HH

#include "Parsable.hh"

class Light : public Parsable {
public:
  Light();

  ~Light() = default;
  Light(const Light &other) = default;
  Light(Light &&other) = default;
  Light &operator=(const Light &other) = default;
  Light &operator=(Light &&other) = default;

  const Position &getPosition() const;
  unsigned int getColor() const;
  double getIntensity() const;

protected:
  Position pos;
  unsigned int color = 0;
  double intensity = 1;
};

#endif /* end of include guard: RT_LIGHT_HH */
