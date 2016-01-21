#ifndef RT_CAMERA_HH
#define RT_CAMERA_HH

#include "SceneObj.hh"

class Camera : public SceneObj
{
public:
    Camera();

    ~Camera() = default;
    Camera(const Camera& other) = default;
    Camera(Camera&& other) = default;
    Camera& operator=(const Camera& other) = default;
    Camera& operator=(Camera&& other) = default;
    
    bool intersect() const {};
};

#endif /* end of include guard: RT_CAMERA_HH */
