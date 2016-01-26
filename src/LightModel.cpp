#include "LightModel.hh"

LightModel::LightModel(const std::vector<std::shared_ptr<Light>>& lights) :
    lights(lights) {}
    
unsigned int
LightModel::applyLights(const std::pair<std::shared_ptr<SceneObj>, double>& objK) {
    std::shared_ptr<SceneObj> obj = objK.first;
    
    return obj->getColor();
}