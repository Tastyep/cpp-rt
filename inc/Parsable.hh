#ifndef RT_PARSABLE_HH
#define RT_PARSABLE_HH

#include "Utility.hpp"

#include <functional>
#include <map>
#include <vector>

class Parsable {
public:
  Parsable() = default;

  virtual ~Parsable() = default;
  Parsable(const Parsable &other) = default;
  Parsable(Parsable &&other) = default;
  Parsable &operator=(const Parsable &other) = default;
  Parsable &operator=(Parsable &&other) = default;

  virtual bool parseArgs(std::stringstream &ss);

protected:
  bool parseArg(const std::vector<std::string> &tokens);

protected:
  std::map<std::string, std::reference_wrapper<unsigned int>> IntegerValues;
  std::map<std::string, std::reference_wrapper<double>> FloatingValues;
};

#endif /* end of include guard: RT_PARSABLE_HH */
