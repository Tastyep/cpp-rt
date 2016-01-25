#ifndef RT_CAMERA_HH
#define RT_CAMERA_HH

#include "Parsable.hh"

class Camera : public Parsable
{
public:
    Camera();

    ~Camera() = default;
    Camera(const Camera& other) = default;
    Camera(Camera&& other) = default;
    Camera& operator=(const Camera& other) = default;
    Camera& operator=(Camera&& other) = default;
    
    const Position& getPosition() const;

private:
    Position pos;
};

#endif /* end of include guard: RT_CAMERA_HH */
