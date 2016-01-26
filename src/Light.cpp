#include "Light.hh"

Light::Light() {
    IntegerValues = {{"color", color}};
    FloatingValues = {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}};
}