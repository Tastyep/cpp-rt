#include "Camera.hh"

Camera::Camera() {
//    IntegerValues = {};
    FloatingValues = {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}};
}

const Position& Camera::getPosition() const {
    return pos;
}