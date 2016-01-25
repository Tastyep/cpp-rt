#ifndef RT_SCENE_OBJ
#define RT_SCENE_OBJ

#include "Objects.hpp"
#include "Parsable.hh"

#include <map>
#include <array>

class SceneObj : public Objects, public Parsable
{
public:
    SceneObj() = default;

    virtual double intersect(const std::array<double, 3>& rayVec, const Camera& camera) const = 0;
    
    const Position& getPosition() const;
    unsigned int getColor() const;

protected:
  Position pos;
  unsigned int color = 0;
};

#endif /* end of include guard: RT_SCENE_OBJ */
