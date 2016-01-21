#include "Parser.hh"
#include "Sphere.hh"

#include <iostream>
#include <sstream>

Parser::Parser() : _validScene(false)    {
  _shapes.emplace("Sphere", [this]() { _objects.emplace_back(new Sphere()); });
  _shapes.emplace("Camera", [this]() { _validScene = true; });
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
  std::shared_ptr<Objects> obj = nullptr;

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
      if (obj == nullptr)
        continue;
      else
        obj->parseArgs(ss);
    } else {
      it->second();
      obj = _objects.back();
    }
  }
  return true;
}

const std::vector<std::shared_ptr<Objects>> &Parser::getObjects() const {
  return _objects;
}

const Camera& Parser::getCamera() const {
    return _camera;
}
