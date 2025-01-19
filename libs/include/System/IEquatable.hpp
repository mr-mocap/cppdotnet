#pragma once


namespace System
{

template <class Derived>
struct IEquatable
{
    virtual bool Equals(const Derived &other) const = 0;
};

}