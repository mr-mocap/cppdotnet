#pragma once

#include <functional>


namespace System
{

template <typename RetType, typename ...ArgTypes>
class Delegate
{
public:
    Delegate() noexcept = default;
    Delegate(std::nullptr_t value) noexcept
        :
        _callable( value )
    {
    }

    Delegate(std::function<RetType (ArgTypes ...)> fn)
        :
        _callable( fn )
    {
    }

    Delegate(const Delegate &other)
        :
        _callable( other._callable )
    {
    }

    Delegate(Delegate &&other) noexcept
        :
        _callable( std::move(other._callable) )
    {
    }

    bool HasSingleTarget() const { return true; }

    RetType operator()(ArgTypes ...args) const
    {
        return _callable(args...);
    }

    operator bool() const { return (bool)_callable; }
protected:
    std::function<RetType (ArgTypes ...args)> _callable;
};


template <typename RetType, typename ...ArgTypes>
class MulticastDelegate
{
public:

    bool HasSingleTarget() const { return false; }
#if 0
    RetType operator()(typename ArgTypes ...args) const
    {
        return _callable(args...);
    }
#endif
protected:
};

}