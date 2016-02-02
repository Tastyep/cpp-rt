#include "Light.hh"

Light::Light() {
    IntegerValues = {{"color", color}};
    FloatingValues = {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}};
}

const Position& Light::getPosition() const {
    return pos;
}

unsigned int Light::getColor() const {
    return color;
}