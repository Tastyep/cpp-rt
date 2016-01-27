#include "SceneObj.hh"

#include <iostream>
#include <stdexcept>

void SceneObj::applyTransformations(Camera& camera, Vector& rayVec) const {
    camera.pos.x -= pos.x;
    camera.pos.y -= pos.y;
    camera.pos.z -= pos.z;
    // apply rotation next
}


const Position& SceneObj::getPosition() const {
    return pos;
}

const LightParameters& SceneObj::getLightParameters() const {
    return light;
}

unsigned int SceneObj::getColor() const {
    return color;
}