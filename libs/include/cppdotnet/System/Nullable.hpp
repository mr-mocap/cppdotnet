#pragma once

#include <cppdotnet/System/Exception.hpp>
#include <optional>
#include <utility>


namespace System
{

template <class T>
class Nullable
{
public:
    Nullable() = default;
    constexpr Nullable(const T &init_value)
        :
        _data{ init_value }
    {
    }
    Nullable(const Nullable &other) = default;
    Nullable(Nullable &&other) = default;

    constexpr TypeCode GetTypeCode() const { return HasValue() ? TypeCode::Object : TypeCode::Empty; }

    constexpr bool HasValue() const
    {
        return _data.has_value();
    }

    constexpr const T &Value() const &
    {
        if ( !HasValue() )
            ThrowWithTarget( InvalidOperationException( "HasValue property is false" ) );
        return _data.value();
    }

    constexpr T &Value() &
    {
        if ( !HasValue() )
            ThrowWithTarget( InvalidOperationException( "HasValue property is false" ) );
        return _data.value();
    }


    template <class U = std::remove_cv_t<T>>
    constexpr T GetValueOrDefault(U &&default_value) const &
    {
        return _data.value_or( default_value );
    }

    template <class U = std::remove_cv_t<T>>
    constexpr T GetValueOrDefault(U &&default_value) &&
    {
        return _data.value_or( default_value );
    }

    constexpr T GetValueOrDefault() const
    {
        return GetValueOrDefault( T{} );
    }


    Nullable &operator =(std::nullopt_t empty) noexcept
    {
        _data = empty;
        return *this;
    }

    constexpr Nullable &operator =(const Nullable &other)
    {
        _data = other._data;
        return *this;
    }

    constexpr Nullable &operator =(Nullable &&other) noexcept
    {
        _data = std::move( other );
        return *this;
    }

    template <class U = std::remove_cv_t<T>>
    constexpr Nullable &operator =(U &&new_value)
    {
        _data = std::forward<U>( new_value );
        return *this;
    }

    bool operator ==(const Nullable &other) const
    {
        return ( _data.has_value() == other._data.has_value() ) &&
               ( !_data.has_value() || ( _data.value() == other._data.value() ) );
    }

    bool operator ==(const T &other) const
    {
        return  _data.has_value() && ( _data.value() == other );
    }

    constexpr operator T() const
    {
        return GetValueOrDefault();
    }
protected:
    std::optional<T> _data;
};

}