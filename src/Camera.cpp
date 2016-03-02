#include "Camera.hh"

Camera::Camera() {
  //    IntegerValues = {};
  FloatingValues = {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}};
}

Camera::Camera(const Position &pos) : pos(pos) {}