#ifndef RT_PARSER_HH
#define RT_PARSER_HH

#include "Objects.hpp"
#include "Camera.hh"

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <functional>
#include <memory>

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
  const std::vector<std::shared_ptr<Objects>> &getObjects() const;
  const Camera& getCamera() const;

private:
  bool readFile(std::ifstream &file);

private:
  bool _validScene;
  std::vector<std::shared_ptr<Objects>> _objects;
  Camera _camera;
  std::map<std::string, std::function<void()>> _shapes;
};

#endif /* end of include guard: RT_PARSER_HH */
