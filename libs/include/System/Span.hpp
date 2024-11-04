#pragma once

#include <span>

namespace System
{

template <class Type>
class Span
{
public:
    constexpr Span() = default;
    explicit constexpr Span(Type &object)
        :
        _data{ &object, 1 }
    {
    }
    Span(Type &&object) = delete;


    static constexpr Span<Type> Empty() { return Span<Type>(); }

    constexpr bool IsEmpty() const { return _data.empty(); }

    constexpr size_t Length() const { return _data.size(); }

    constexpr const Type &operator [](size_t index) const
    {
        return _data[index];
    }

    constexpr Type &operator [](size_t index)
    {
        return _data[index];
    }
protected:
    std::span<Type> _data;
};

}