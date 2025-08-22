#include <numbers>
//#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <type_traits>

namespace System
{

class Math
{
public:

    static constexpr double E   = std::numbers::e;
    static constexpr double PI  = std::numbers::pi;
    static constexpr double Tau = 2.0 * std::numbers::pi;

    static short  Abs(short value)  { return static_cast<short>( std::abs(value) ); }
    static int    Abs(int value)    { return std::abs(value); }
    static long   Abs(long value)   { return std::abs(value); }
    static float  Abs(float value)  { return std::fabs(value); }
    static double Abs(double value) { return std::fabs(value); }

    static float  Ceiling(float value)  { return std::ceil(value); }
    static double Ceiling(double value) { return std::ceil(value); }

    static float  Floor(float value)  { return std::floor(value); }
    static double Floor(double value) { return std::floor(value); }

    static float  Truncate(float value)  { return std::trunc(value); }
    static double Truncate(double value) { return std::trunc(value); }

    static float  Round(float value) { return std::round(value); }
    static double Round(double value) { return std::round(value); }

    template <class T>
    static constexpr T Clamp(T value, T lower_bound, T upper_bound) { return std::clamp(value, lower_bound, upper_bound); }

    static float  Copysign(float value, float sgn) { return std::copysign(value, sgn); }
    static double Copysign(float value, double sgn) { return std::copysign(value, sgn); }

    static float  Exp(float value) { return std::exp(value); }
    static double Exp(double value) { return std::exp(value); }

    static float  Log(float value) { return std::log(value); }
    static double Log(double value) { return std::log(value); }

    static float  Log10(float value) { return std::log10(value); }
    static double Log10(double value) { return std::log10(value); }

    static float  Log2(float value) { return std::log2(value); }
    static double Log2(double value) { return std::log2(value); }

    static float  Pow(float base, float exp) { return std::pow(base, exp); }
    static double Pow(double base, double exp) { return std::pow(base, exp); }

    template <class T>
    static T Min(T v1, T v2)
    {
        if constexpr ( std::is_floating_point_v<T> )
            return std::fmin(v1, v2);
        else
            return std::min(v1, v2);
    }

    template <class T>
    static T Max(T v1, T v2)
    {
        if constexpr ( std::is_floating_point_v<T> )
            return std::fmax(v1, v2);
        else
            return std::max(v1, v2);
    }

    template <class T>
    static int Sign(T value)
    {
        if constexpr ( std::is_integral_v<T> )
        {
            if ( value < 0 )
                return -1;
            else if ( value > 0 )
                return 1;
            else
                return 0;
        }
        else if constexpr ( std::is_floating_point_v<T> )
        {
            if ( value < 0.0 )
                return -1;
            else if ( value > 0.0 )
                return 1;
            else
                return 0; // TODO: Should we really check for being VERY close to 0?
        }
    }

    // Trigonometric
    static float  Acos(float value) { return std::acos(value); }
    static double Acos(double value) { return std::acos(value); }

    static float  Asin(float value) { return std::asin(value); }
    static double Asin(double value) { return std::asin(value); }

    static float  Atan(float value) { return std::atan(value); }
    static double Atan(double value) { return std::atan(value); }

    static float  Atan2(float x, float y) { return std::atan2(x,y); }
    static double Atan2(double x, double y) { return std::atan2(x,y); }

    static float  Cos(float value) { return std::cos(value); }
    static double Cos(double value) { return std::cos(value); }

    static float  Sin(float value) { return std::sin(value); }
    static double Sin(double value) { return std::sin(value); }

    // Hyperbolic
    static float  Acosh(float value) { return std::acosh(value); }
    static double Acosh(double value) { return std::acosh(value); }

    static float  Asinh(float value) { return std::asinh(value); }
    static double Asinh(double value) { return std::asinh(value); }

    static float  Atanh(float value) { return std::atanh(value); }
    static double Atanh(double value) { return std::atanh(value); }

    static float  Cosh(float value) { return std::cosh(value); }
    static double Cosh(double value) { return std::cosh(value); }

    static float  Sinh(float value) { return std::sinh(value); }
    static double Sinh(double value) { return std::sinh(value); }
};

}