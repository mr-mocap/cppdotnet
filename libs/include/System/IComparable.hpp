
namespace System
{

template <class Derived>
struct IComparable
{
    int CompareTo(const Derived &other) const;
};

}