#ifndef RT_LIGHT_HH
#define RT_LIGHT_HH

#include "Parsable.hh"

class Light : public Parsable
{
public:
    Light();

    ~Light() = default;
    Light(const Light& other) = default;
    Light(Light&& other) = default;
    Light& operator=(const Light& other) = default;
    Light& operator=(Light&& other) = default;

protected:
  Position pos;
  unsigned int color = 0;
};

#endif /* end of include guard: RT_LIGHT_HH */
