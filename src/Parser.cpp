#include "Parser.hh"
#include "Sphere.hh"
#include "Rectangle.hh"

#include <iostream>

Parser::Parser() : _validScene(false) {
  _shapes.emplace("Sphere", [this]() { _objects.emplace_back(new Sphere()); });
  _shapes.emplace("Rectangle",
                  [this]() { _objects.emplace_back(new Rectangle()); });
  _shapes.emplace("Light", [this]() { _lights.emplace_back(new Light()); });

  _elements.emplace("Camera",
                    ParsableWrapper(_camera, [this]() { _validScene = true; }));
}

bool Parser::parse(const std::string &fileName) {
  std::ifstream file;
  bool ret = false;

  file.open(fileName);
  if (file.is_open()) {
    ret = this->readFile(file);
    file.close();
  } else
    std::cerr << "Could not open the file named \"" << fileName << "\""
              << std::endl;
  return ret;
}

bool Parser::readFile(std::ifstream &file) {
  std::string line;
  std::string keyword;
  std::size_t pos;
  Parsable *obj = nullptr;

  while (std::getline(file, line)) {
    std::stringstream ss(line);

    if (line.empty())
      continue;
    pos = line.find_first_of(" \t");
    if (pos == std::string::npos)
      pos = line.size();
    else
      ++pos;
    keyword = line.substr(0, pos);

    auto it = _shapes.find(keyword);
    if (it == _shapes.end()) {
      auto it2 = _elements.find(keyword);

      if (it2 == _elements.end()) {
        if (obj == nullptr)
          continue;
        else
          obj->parseArgs(ss);
      } else {
        it2->second.callback();
        obj = std::addressof(it2->second.obj);
      }
    } else {
      it->second();
      if (keyword.compare("Light") == 0)
        obj = _lights.back().get();
      else
        obj = _objects.back().get();
    }
  }
  return true;
}

const std::vector<std::shared_ptr<SceneObj>> &Parser::getObjects() const {
  return _objects;
}

const std::vector<std::shared_ptr<Light>> &Parser::getLights() const {
  return _lights;
}

const Camera &Parser::getCamera() const { return _camera; }
