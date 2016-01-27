#ifndef RT_MATH_HH
#define RT_MATH_HH

#include "Utility.hpp"

#include <array>

class Math
{
public:
    static double constexpr eps = 0.000001;
public:
    Math() = default;

    ~Math() = default;
    Math(const Math& other) = default;
    Math(Math&& other) = default;
    Math& operator=(const Math& other) = default;
    Math& operator=(Math&& other) = default;

    double solveSecond(const Vector& coefs, std::array<double, 2> solutions) const;
    unsigned int multiplyColor(unsigned int color, const Vector& vec) const;
    unsigned int multiplyColor(unsigned int color, double value) const;
    unsigned int addColor(unsigned int color, unsigned int color2) const;

private:
    double getPositiveMin(const auto &array) const;

};

#endif /* end of include guard: RT_MATH_HH */
