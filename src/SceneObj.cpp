#include "SceneObj.hh"

#include <iostream>
#include <stdexcept>

void SceneObj::apply_transformations(Camera& camera, std::array<double, 3>& rayVec) const {
    camera.pos.x -= pos.x;
    camera.pos.y -= pos.y;
    camera.pos.z -= pos.z;
    // apply rotation next
}


const Position& SceneObj::getPosition() const {
    return pos;
}

unsigned int SceneObj::getColor() const {
    return color;
}