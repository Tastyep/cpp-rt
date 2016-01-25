#ifndef RT_PARSABLE_HH
#define RT_PARSABLE_HH

#include <map>
#include <functional>
#include <vector>

struct Position {
  double x;
  double y;
  double z;

  Position(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

class Parsable
{
public:
    Parsable() = default;

    ~Parsable() = default;
    Parsable(const Parsable& other) = default;
    Parsable(Parsable&& other) = default;
    Parsable& operator=(const Parsable& other) = default;
    Parsable& operator=(Parsable&& other) = default;

    virtual bool parseArgs(std::stringstream &ss);

protected:
    bool parseArg(const std::vector<std::string>& tokens);
    
protected:
    std::map<std::string, std::reference_wrapper<unsigned int>> IntegerValues;
    std::map<std::string, std::reference_wrapper<double>> FloatingValues;
};

#endif /* end of include guard: RT_PARSABLE_HH */
