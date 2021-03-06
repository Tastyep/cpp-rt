#ifndef RT_PARSER_HH
#define RT_PARSER_HH

#include "Camera.hh"
#include "Light.hh"
#include "SceneObj.hh"

#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

struct ParsableWrapper {
  Parsable &obj;
  std::function<void()> callback;

  ParsableWrapper(Parsable &p, const std::function<void()> &callback)
      : obj(p), callback(callback) {}
};

class Parser {
public:
  Parser();

  ~Parser() = default;
  Parser(const Parser &other) = default;
  Parser(Parser &&other) = default;
  Parser &operator=(const Parser &other) = default;
  Parser &operator=(Parser &&other) = default;

public:
  bool parse(const std::string &fileName);
  const std::vector<std::shared_ptr<SceneObj>> &getObjects() const;
  const std::vector<std::shared_ptr<Light>> &getLights() const;
  const Camera &getCamera() const;

private:
  bool readFile(std::ifstream &file);

private:
  bool _validScene;
  std::vector<std::shared_ptr<SceneObj>> _objects;
  std::vector<std::shared_ptr<Light>> _lights;
  Camera _camera;
  std::map<std::string, ParsableWrapper> _elements;
  std::map<std::string, std::function<void()>> _shapes;
};

#endif /* end of include guard: RT_PARSER_HH */
