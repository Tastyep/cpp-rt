#include "Sphere.hh"

Sphere::Sphere() {
  IntegerValues = {{"radius", radius}, {"color", color}};
  FloatingValues = {{"x", pos.x}, {"y", pos.y}};
}

bool Sphere::intersect() const {}

bool Sphere::parseArgs(std::stringstream &ss) {
    std::vector<std::string> tokens;
    std::string token;
    
    while (ss >> token) {
        tokens.push_back(token);
    }
    if (tokens.size() != 3)
        return true;
    return this->parseArg(tokens);
}
