#ifndef RT_MATH_HH
#define RT_MATH_HH

#include <array>
#include <cmath>

class Math
{
public:
    Math() = default;

    ~Math() = default;
    Math(const Math& other) = default;
    Math(Math&& other) = default;
    Math& operator=(const Math& other) = default;
    Math& operator=(Math&& other) = default;

    double solveSecond(const std::array<double, 3>& coefs, std::array<double, 2> solutions) const;

private:
    double getPositiveMin(const auto &array) const;

};

#endif /* end of include guard: RT_MATH_HH */
