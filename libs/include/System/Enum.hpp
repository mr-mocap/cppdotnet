#pragma once

#include "System/Exception.hpp"
#include <span>
#include <optional>

namespace System
{

template <class DerivedType, class EnumImplementationType = int>
class Enum
{
public:
    using value_type = EnumImplementationType;

    static const std::span<const std::string_view> GetNames()
    {
        return DerivedType::GetNamesImplementation();
    }

    static const std::span<const value_type> GetValues()
    {
        return DerivedType::GetValuesImplementation();
    }

    const std::string_view GetName() const
    {
        return static_cast<const DerivedType *>(this)->GetNameImplementation();
    }

    static bool IsDefined(value_type value)
    {
        return DerivedType::IsDefinedImplementation(value);
    }

    static bool IsDefined(const std::string_view value_string)
    {
        return DerivedType::IsDefinedImplementation(value_string);
    }

    static value_type Parse(const std::string_view value_string)
    {
        return DerivedType::ParseImplementation(value_string);
    }

    static std::optional<value_type> TryParse(const std::string_view value_string)
    {
        return DerivedType::TryParseImplementation(value_string);
    }

    bool HasFlag(value_type value) const
    {
        return (value & _currentValue) == value;
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