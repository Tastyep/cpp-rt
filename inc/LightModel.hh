#ifndef RT_LIGHTMODEL_HH
#define RT_LIGHTMODEL_HH

#include "Light.hh"
#include "SceneObj.hh"

#include <vector>
#include <memory>

class LightModel
{
public:
    LightModel(const std::vector<std::shared_ptr<Light>>& lights);

    ~LightModel() = default;
    LightModel(const LightModel& other) = default;
    LightModel(LightModel&& other) = default;
    LightModel& operator=(const LightModel& other) = default;
    LightModel& operator=(LightModel&& other) = default;
    
    unsigned int applyLights(const std::pair<std::shared_ptr<SceneObj>, double>& objK);
    
private:
    const std::vector<std::shared_ptr<Light>>& lights;
};

#endif /* end of include guard: RT_LIGHTMODEL_HH */
