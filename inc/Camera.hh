#ifndef RT_CAMERA_HH
#define RT_CAMERA_HH

#include "Parsable.hh"

class Camera : public Parsable {
public:
  Camera();
  Camera(const Position &pos);

  ~Camera() = default;
  Camera(const Camera &other) = default;
  Camera(Camera &&other) = default;
  Camera &operator=(const Camera &other) = default;
  Camera &operator=(Camera &&other) = default;

  Camera &operator=(const Position &pos) { this->pos = pos; }
  Position pos;
};

#endif /* end of include guard: RT_CAMERA_HH */
