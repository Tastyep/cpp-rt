#include "Color.hh"
#include <iostream>
Color::Color(unsigned int color)
    : r((color >> 16) & 0xFF), g((color >> 8) & 0xFF), b(color & 0xFF) {}

Color::Color(unsigned int r, unsigned int g, unsigned int b)
    : r(r), g(g), b(b) {}

unsigned int Color::toInteger() const {
  unsigned int color;

  color = this->r << 16;
  color |= (this->g << 8);
  color |= this->b;
  return color;
}

void Color::mix(const Color &color, double amount) {
  double Oamount = 1.0 - amount;

  this->r = static_cast<double>(this->r) * Oamount +
            static_cast<double>(color.r) * amount;
  this->g = static_cast<double>(this->g) * Oamount +
            static_cast<double>(color.g) * amount;
  this->b = static_cast<double>(this->b) * Oamount +
            static_cast<double>(color.b) * amount;
}

void Color::limit(unsigned int r, unsigned int g, unsigned int b) {
  if (this->r > r)
    this->r = r;
  if (this->g > g)
    this->g = g;
  if (this->b > b)
    this->b = b;
}
