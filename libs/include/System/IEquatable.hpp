
namespace System
{

template <class Derived>
struct IEquatable
{
    constexpr bool Equals(const Derived &other) const;
};

}