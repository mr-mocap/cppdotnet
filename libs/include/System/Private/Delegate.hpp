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

    Delegate(const Delegate &other) = default;
    Delegate(Delegate &&other) noexcept = default;

    Delegate &operator =(const Delegate &) = default;
    Delegate &operator =(Delegate &&) = default;

    Delegate &operator =(const std::function<RetType (ArgTypes ...)> &fn)
    {
        _callable = fn;
        return *this;
    }

    Delegate &operator =(std::function<RetType (ArgTypes ...)> &&other)
    {
        _callable = std::move(other);
        return *this;
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