#include "SceneObj.hh"

#include <iostream>
#include <stdexcept>

const Position& SceneObj::getPosition() const {
    return pos;
}

unsigned int SceneObj::getColor() const {
    return color;
}