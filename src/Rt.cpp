#include "Rt.hh"

Rt::Rt(const Camera &camera,
       const std::vector<std::shared_ptr<SceneObj>> &objects)
    : camera(camera), objects(objects) {}

void
Rt::computeRayVec(std::array<double, 3>& rayVec, unsigned int x, unsigned int y, sf::Vector2u& screenSize) const {
    const Position camPos = camera.getPosition();

    rayVec[0] = Rt::Dist - camPos.x;
    rayVec[1] = (screenSize.x / 2 - x) - camPos.y;
    rayVec[2] = (screenSize.y / 2 - y) - camPos.z;
    // Apply rotation
}

std::shared_ptr<SceneObj> Rt::getClosestObj(const auto& rayVec) {
    double k = 0;
    double kmin = 0;
    std::shared_ptr<SceneObj> savedObj = nullptr;
    
    for (const auto& object : this->objects) {
        k = object->intersect(rayVec, this->camera);
        if (k > 0 && (k < kmin || kmin == 0)) {
            kmin == k;
            savedObj = object;
        }
    }
    return savedObj;
}

unsigned int Rt::computePixelColor(const std::array<double, 3>& rayVec) {
    std::shared_ptr<SceneObj> closestObj = this->getClosestObj(rayVec);
    unsigned int color;
    
    return 0xFFFFFF;
}