#pragma once

#include "System/Exception.hpp"
#include <span>
#include <optional>

namespace System
{

template <class DerivedType, class EnumImplementationType>
class Enum
{
public:
    using value_type = EnumImplementationType;

    const std::span<const std::string_view> GetNames() const
    {
        return static_cast<const DerivedType *>(this)->GetNames();
    }

    const std::span<value_type> GetValues() const
    {
        return static_cast<const DerivedType *>(this)->GetValues();
    }

    const std::string_view GetName() const
    {
        return static_cast<const DerivedType *>(this)->GetName();
    }

    static bool IsDefined(value_type value)
    {
        return DerivedType::IsDefined(value);
    }

    static bool IsDefined(const std::string_view value_string)
    {
        return DerivedType::IsDefined(value_string);
    }

    static value_type Parse(const std::string_view value_string)
    {
        return DerivedType::Parse(value_string);
    }

    static std::optional<value_type> TryParse(const std::string_view value_string)
    {
        return DerivedType::TryParse(value_string);
    }

    operator value_type () const { return _currentValue; }

    Enum &operator =(value_type v)
    {
        _currentValue = v;
        return *this;
    }

    Enum &operator =(const std::string_view value_string)
    {
        Enum::operator =( Parse(value_string) );
        return *this;
    }
protected:
    value_type  _currentValue{};

    Enum(value_type v) : _currentValue{ v } { }
};

}