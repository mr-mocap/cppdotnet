module;

export module System:IComparable;


namespace System
{

export
template <class Derived>
struct IComparable
{
    int CompareTo(const Derived &other) const;
};

}