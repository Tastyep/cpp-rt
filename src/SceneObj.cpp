#include "SceneObj.hh"

#include <iostream>
#include <stdexcept>

void SceneObj::applyTransformations(Position &vecPos, Vector &rayVec) const {
  vecPos.x -= pos.x;
  vecPos.y -= pos.y;
  vecPos.z -= pos.z;
  // apply rotation next
}

const Position &SceneObj::getPosition() const { return pos; }

const LightParameters &SceneObj::getLightParameters() const { return light; }

unsigned int SceneObj::getColor() const { return color; }

float SceneObj::getReflectionIndex() const { return reflection; }

float SceneObj::getTransparencyIndex() const { return alpha; }

float SceneObj::getAbsorbanceIdx() const { return absorbance; }
