#ifndef RT_SCENE_OBJ
#define RT_SCENE_OBJ

#include "Objects.hpp"
#include "Parsable.hh"

#include <map>
#include <array>
#include <memory>

struct LightParameters {
    double Ia;
    double Id;
    double Is;
};

class SceneObj : public Objects, public Parsable
{
public:
    SceneObj() = default;

    virtual double intersect(Vector rayVec, Camera camera) const = 0;
    virtual void calcNormal(Vector& normVec, const Position& impact) const = 0;
    
    const Position& getPosition() const;
    const LightParameters& getLightParameters() const;
    unsigned int getColor() const;

    void applyTransformations(Camera& camera, Vector& rayVec) const;

protected:
  Position pos;
  LightParameters light;
  unsigned int color = 0;
};

#endif /* end of include guard: RT_SCENE_OBJ */
