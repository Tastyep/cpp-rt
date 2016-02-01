#include "Rectangle.hh"
#include "Math.hh"

#include <iostream>

Rectangle::Rectangle() {
  IntegerValues = {{"color", color}};
  FloatingValues = {{"x", pos.x},       {"y", pos.y},     {"z", pos.z},
                    {"Ia", light.Ia},   {"Id", light.Id}, {"Is", light.Is},
                    {"height", height}, {"width", width}};
}

double Rectangle::intersect(Vector rayVec, Camera camera) const {
  // this->applyTransformations(camera, rayVec);
  // Vector objVec(pos.x - camera.pos.x, pos.y - camera.pos.y,
  //               pos.z - camera.pos.z);
  // Vector AB(pos.x + this->height, pos.y, pos.z);
  // Vector AD(pos.x + this->height, pos.y + this->width, pos.z);
  // Vector Normal = AB * AD;
  // double d;
  // 
  // d = objVec.doc(normal)
  return -1;
}

void Rectangle::calcNormal(Vector &normVec, const Position &impact) const {
  normVec.x = pos.x + this->height;
  normVec.y = pos.y - this->width;
  normVec.z = pos.z;
}