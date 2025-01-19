#pragma once

#include "System/Exception.hpp"
#include "System/IConvertible.hpp"
#include <span>
#include <optional>
#include <algorithm>
#include <array>
#include <utility>
#include <ranges>
#include <cassert>

namespace System
{
#if 0
template <typename Derived, typename T>
struct GetEnumType
{
    using type = T;
};

template <typename Derived>
struct GetEnumType<Derived, void>
{
    using type = Derived::Values;
};

template <class DerivedType, class EnumImplementationType = void>
class Enum
{
public:
    using value_type = GetEnumType<DerivedType, EnumImplementationType>::type;

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

    template <typename DArg = DerivedType>
    static bool IsDefined(typename DArg::Values value)
    {
        return std::ranges::find( GetValues(), static_cast<value_type>(value) ) != GetValues().end();
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
#else
template <class EnumPolicy>
class Enum : public EnumPolicy, public IConvertible
{
public:
    Enum() = default;
    Enum(EnumPolicy::value_type v) : _currentValue{ v } { }

    static const auto GetNames()
    {
        return MakeNames();
    }

    static const auto GetValues()
    {
        return MakeValues();
    }

    static const auto GetValuesAsUnderlyingType()
    {
        auto transform_fn = [](const typename EnumPolicy::value_type item) { return static_cast<typename EnumPolicy::underlying_type>(item); };

        return MakeValues() | std::views::transform( transform_fn );
    }

    static const std::string_view GetName(typename EnumPolicy::value_type value)
    {
        auto found = std::ranges::find( EnumPolicy::NameValueArray(),
                                        value,
                                        &EnumPolicy::name_value_pair_type::second
                                      );

        if ( found == EnumPolicy::NameValueArray().end() )
            return {};

        return found->first;
    }

    const std::string_view GetName() const
    {
        return GetName( _currentValue );
    }

    static bool IsDefined(typename EnumPolicy::value_type value)
    {
        return std::ranges::find( GetValues(), value ) != GetValues().end();
    }

    static bool IsDefined(typename EnumPolicy::underlying_type value)
    {
        return std::ranges::find( GetValues(), static_cast<typename EnumPolicy::value_type>(value) ) != GetValues().end();
    }

    static bool IsDefined(const std::string_view value_string)
    {
        return std::ranges::find( GetNames(), value_string ) != GetNames().end();
    }

    bool HasFlag(typename EnumPolicy::value_type value) const
    {
        return (static_cast<EnumPolicy::underlying_type>(value) & static_cast<EnumPolicy::underlying_type>(_currentValue)) == static_cast<EnumPolicy::underlying_type>(value);
    }

    static typename EnumPolicy::value_type Parse(const std::string_view value_string)
    {
        if ( value_string.empty() )
            ThrowWithTarget( System::ArgumentException{ "Argument is empty", "value_string" } );

        if ( !IsDefined(value_string) )
            ThrowWithTarget( System::ArgumentException{ "Argument does not name a defined constant", "value_string" } );

        // First, check for a name...
        for (const typename EnumPolicy::name_value_pair_type &i : EnumPolicy::NameValueArray())
            if ( i.first == value_string )
                return i.second;
        
        typename EnumPolicy::underlying_type converted;

        // We don't have a name, so let's convert to an integer type...
        auto [ptr, ec] = std::from_chars( value_string.data(), value_string.data() + value_string.size(),
                                          converted);
        
        if ( ec == std::errc::invalid_argument )
            ThrowWithTarget( System::ArgumentException{ "Argument does not contain Enumeration information", "value_string" } );
        else if ( ec == std::errc::result_out_of_range )
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "value_string" } );
        else if ( ec != std::errc() )
            ThrowWithTarget( System::ArgumentException{ "Argument does not contain Enumeration information", "value_string" } );

        assert( ec == std::errc() );

        typename EnumPolicy::value_type casted{ static_cast<typename EnumPolicy::value_type>(converted) };

        if ( !IsDefined( casted ) )
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "value_string" } );

        // We have one of the valid values!
        return casted;
    }

    static std::optional<typename EnumPolicy::value_type> TryParse(const std::string_view value_string)
    {
        // First, check for a name...
        for (const typename EnumPolicy::name_value_pair_type &i : EnumPolicy::NameValueArray())
            if ( i.first == value_string )
                return i.second;
        
        typename EnumPolicy::underlying_type converted;

        // We don't have a name, so let's convert to an integer type...
        auto [ptr, ec] = std::from_chars( value_string.data(), value_string.data() + value_string.size(),
                                          converted);
        
        if ( ec == std::errc::invalid_argument )
            return {};
        else if ( ec == std::errc::result_out_of_range )
            return {};
        else if ( ec != std::errc() )
            return {};
        
        assert( ec == std::errc() );

        typename EnumPolicy::value_type casted{ static_cast<typename EnumPolicy::value_type>(converted) };

        if ( !IsDefined( casted ) )
            return {};

        // We have one of the valid values!
        return casted;
    }

    operator typename EnumPolicy::value_type () const { return _currentValue; }

    Enum &operator =(typename EnumPolicy::value_type v)
    {
        _currentValue = v;
        return *this;
    }

    // IConvertible Interface
    TypeCode GetTypeCode() const override
    {
        if constexpr ( std::is_same_v<typename EnumPolicy::underlying_type, char> )
            return TypeCode::Char;
        else if constexpr ( std::is_same_v<typename EnumPolicy::underlying_type, int16_t> )
            return TypeCode::Int16;
        else if constexpr ( std::is_same_v<typename EnumPolicy::underlying_type, int32_t> )
            return TypeCode::Int32;
        else if constexpr ( std::is_same_v<typename EnumPolicy::underlying_type, int64_t> )
            return TypeCode::Int64;
        else if constexpr ( std::is_same_v<typename EnumPolicy::underlying_type, uint16_t> )
            return TypeCode::UInt16;
        else if constexpr ( std::is_same_v<typename EnumPolicy::underlying_type, uint32_t> )
            return TypeCode::UInt32;
        else if constexpr ( std::is_same_v<typename EnumPolicy::underlying_type, uint64_t> )
            return TypeCode::UInt64;
        else
            static_assert("GetTypeCode() Not Implemented for this EnumPolicy::underlying_type");
    }

    bool ToBoolean() const override { return _currentValue; }

    std::byte ToByte() const override { return std::byte{_currentValue}; }

    char ToChar() const override { return {_currentValue}; }

    std::int16_t ToInt16() const override { return {_currentValue}; }
    std::int32_t ToInt32() const override { return {_currentValue}; }
    std::int64_t ToInt64() const override { return {_currentValue}; }

    std::uint16_t ToUInt16() const override { return {_currentValue}; }
    std::uint32_t ToUInt32() const override { return {_currentValue}; }
    std::uint64_t ToUInt64() const override { return {_currentValue}; }

    float  ToSingle() const override { return static_cast<float>(_currentValue); }
    double ToDouble() const override { return static_cast<double>(_currentValue); }

    std::string ToString() const override { return std::string{ GetName() }; }

protected:
    EnumPolicy::value_type  _currentValue{};

    static const auto MakeNames()
    {
        return std::views::keys( EnumPolicy::NameValueArray() );
    }

    static const auto MakeValues()
    {
        return std::views::values( EnumPolicy::NameValueArray() );
    }

    static typename EnumPolicy::value_type ParseCommon(const std::string_view value_string)
    {
        if ( value_string.empty() )
            ThrowWithTarget( System::ArgumentException{ "Argument is empty", "value_string" } );

        if ( !IsDefined(value_string) )
            ThrowWithTarget( System::ArgumentException{ "Argument does not name a defined constant", "value_string" } );

        // First, check for a name...
        for (const typename EnumPolicy::name_value_pair_type &i : EnumPolicy::NameValueArray())
            if ( i.first == value_string )
                return i.second;
        
        typename EnumPolicy::underlying_type converted;

        // We don't have a name, so let's convert to an integer type...
        auto [ptr, ec] = std::from_chars( value_string.data(), value_string.data() + value_string.size(),
                                          converted);
        
        if ( ec == std::errc::invalid_argument )
            ThrowWithTarget( System::ArgumentException{ "Argument does not contain Enumeration information", "value_string" } );
        else if ( ec == std::errc::result_out_of_range )
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "value_string" } );
        else if ( ec != std::errc() )
            ThrowWithTarget( System::ArgumentException{ "Argument does not contain Enumeration information", "value_string" } );

        assert( ec == std::errc() );

        typename EnumPolicy::value_type casted{ static_cast<typename EnumPolicy::value_type>(converted) };

        if ( !IsDefined( casted ) )
            return {};

        // We have one of the valid values!
        return casted;
    }
};
#endif
}