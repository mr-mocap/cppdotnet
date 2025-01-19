#pragma once


namespace System
{

template <class Derived>
struct IComparable
{
    virtual int CompareTo(const Derived &other) const = 0;
};

}