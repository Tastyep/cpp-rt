#ifndef RT_MATH_HH
#define RT_MATH_HH

#include "Utility.hpp"

#include <array>
#include <cmath>

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
    double getVectorNorme(const Vector& vec);

private:
    double getPositiveMin(const auto &array) const;

};

#endif /* end of include guard: RT_MATH_HH */
