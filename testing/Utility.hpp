#include <cmath>

inline bool is_approximately_equal_to(float input, float near_to, float tolerance = 0.0002f )
{
    return std::abs(near_to - input) <= tolerance;
}

inline bool is_approximately_equal_to(double input, double near_to, float tolerance = 0.0002f )
{
    return std::abs(near_to - input) <= tolerance;
}