#pragma once

#include "System/Exception.hpp"
#include <span>
#include <optional>
#include <algorithm>

namespace System
{

template <class DerivedType, class EnumImplementationType = int>
class Enum
{
public:
    using value_type = EnumImplementationType;

    static const std::span<const std::string_view> GetNames()
    {
        static const typename DerivedType::name_array_type names{ MakeNames() };

        return std::span( names );
    }

    static const std::span<const value_type> GetValues()
    {
        static const typename DerivedType::value_array_type values{ MakeValues() };

        return std::span( values );
    }

    const std::string_view GetName() const
    {
        return GetName( static_cast<typename DerivedType::Values>(_currentValue) );
    }

    template <typename DArg = DerivedType>
    static const std::string_view GetName(DArg::Values value)
    {
        auto found = std::ranges::find( DerivedType::_name_value_array,
                                        value,
                                        &DerivedType::name_value_pair_type::second
                                      );

        if ( found == DerivedType::_name_value_array.end() )
            return {};

        return found->first;
    }

    static bool IsDefined(value_type value)
    {
        return std::ranges::find( GetValues(), value ) != GetValues().end();
    }

    static bool IsDefined(const std::string_view value_string)
    {
        return std::ranges::find( GetNames(), value_string ) != GetNames().end();
    }

    static value_type Parse(const std::string_view value_string)
    {
        if ( value_string.empty() )
            ThrowWithTarget( System::ArgumentException{ "Argument is empty", "value_string" } );

        if ( !IsDefined(value_string) )
            ThrowWithTarget( System::ArgumentException{ "Argument does not name a defined constant", "value_string" } );

        // First, check for a name...
        for (const typename DerivedType::name_value_pair_type &i : DerivedType::_name_value_array)
            if ( i.first == value_string )
                return i.second;
        
        int converted;

        // We don't have a name, so let's convert to an integer type...
        try
        {
            converted = std::stoi( std::string{value_string} );
        }
        catch(const std::invalid_argument &e)
        {
            ThrowWithTarget( System::ArgumentException{ "Argument does not contain Enumeration information", "value_string" } );
        }
        catch(const std::out_of_range &e)
        {
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "value_string" } );
        }

        // And don't forget to check if it can be represented in the value_type!

        if ( converted < std::numeric_limits<value_type>::min() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "value_string", "Converted value is less than the minimum for this type" } );
        if ( converted > std::numeric_limits<value_type>::max() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "value_string", "Converted value is greater than the maximum for this type" } );

        if ( !IsDefined( static_cast<value_type>(converted) ) )
            return {};

        return static_cast<value_type>(converted);
    }

    static std::optional<value_type> TryParse(const std::string_view value_string)
    {
        // First, check for a name...
        for (const typename DerivedType::name_value_pair_type &i : DerivedType::_name_value_array)
            if ( i.first == value_string )
                return i.second;
        
        int converted;

        // We don't have a name, so let's convert to an integer type...
        try
        {
            converted = std::stoi( std::string{value_string} );
        }
        catch(const std::invalid_argument &e)
        {
            return {};
        }
        catch(const std::out_of_range &e)
        {
            return {};
        }
        
        // And don't forget to check if it can be represented in the value_type!

        if ( converted < std::numeric_limits<value_type>::min() )
            return {};
        if ( converted > std::numeric_limits<value_type>::max() )
            return {};

        // Return the value, even if it is NOT within the list of values!
        return std::optional<value_type>{ static_cast<value_type>(converted) };
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

    template <typename DRetType = DerivedType>
    static typename DRetType::name_array_type  MakeNames()
    {
        typename DRetType::name_array_type array;

        std::ranges::transform( DerivedType::_name_value_array, array.begin(), [](const auto &i) { return i.first; } );
        return array;
    }

    template <typename DRetType = DerivedType>
    static typename DRetType::value_array_type MakeValues()
    {
        typename DRetType::value_array_type array;

        std::ranges::transform( DerivedType::_name_value_array, array.begin(), [](const auto &i) { return i.second; } );
        return array;
    }

};

}