#ifndef RT_Rectangle_HH
#define RT_Rectangle_HH

#include "SceneObj.hh"

class Rectangle : public SceneObj {
public:
  Rectangle();

  ~Rectangle() = default;
  Rectangle(const Rectangle &other) = default;
  Rectangle(Rectangle &&other) = default;
  Rectangle &operator=(const Rectangle &other) = default;
  Rectangle &operator=(Rectangle &&other) = default;

  double intersect(Vector rayVec, Camera camera) const;
  void calcNormal(Vector &normVec, const Position &impact) const;

private:
  double height;
  double width;
};

#endif /* end of include guard: RT_Rectangle_HH */
