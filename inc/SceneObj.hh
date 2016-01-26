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

    virtual double intersect(std::array<double, 3> rayVec, Camera camera) const = 0;
    
    const Position& getPosition() const;
    unsigned int getColor() const;

protected:
    void apply_transformations(Camera& camera, std::array<double, 3>& rayVec) const;

protected:
  Position pos;
  unsigned int color = 0;
};

#endif /* end of include guard: RT_SCENE_OBJ */
