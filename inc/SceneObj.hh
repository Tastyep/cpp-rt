#ifndef RT_SCENE_OBJ
#define RT_SCENE_OBJ

#include "Objects.hpp"

#include <map>
#include <functional>
#include <vector>

class SceneObj : public Objects
{
public:
    SceneObj() = default;

    virtual bool intersect() const = 0;
    virtual bool parseArgs(std::stringstream &ss);

protected:
    bool parseArg(const std::vector<std::string>& tokens);

protected:
  std::map<std::string, std::reference_wrapper<unsigned int>> IntegerValues;
  std::map<std::string, std::reference_wrapper<double>> FloatingValues;
  position pos;
};

#endif /* end of include guard: RT_SCENE_OBJ */
