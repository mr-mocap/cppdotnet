export module System:Enum;

import System:Exception;
export import System:TypeCode;
export import <optional>;
import <algorithm>;
import <array>;
export import <format>;
export import <string_view>;
export import <compare>;
import <utility>;
import <ranges>;
import <cassert>;
import <charconv>;

namespace System
{

export
template <class EnumPolicy>
class Enum : public EnumPolicy
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

    static std::string_view GetName(typename EnumPolicy::value_type value)
    {
        auto found = std::ranges::find( EnumPolicy::NameValueArray(),
                                        value,
                                        &EnumPolicy::name_value_pair_type::second
                                      );

        if ( found == EnumPolicy::NameValueArray().end() )
            return {};

        return found->first;
    }

    std::string_view GetName() const
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

    static bool IsDefined(std::string_view value_string)
    {
        return std::ranges::find( GetNames(), value_string ) != GetNames().end();
    }

    bool HasFlag(typename EnumPolicy::value_type value) const
    {
        return (static_cast<EnumPolicy::underlying_type>(value) & static_cast<EnumPolicy::underlying_type>(_currentValue)) == static_cast<EnumPolicy::underlying_type>(value);
    }

    static typename EnumPolicy::value_type Parse(std::string_view value_string)
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

    static std::optional<typename EnumPolicy::value_type> TryParse(std::string_view value_string)
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

    // IComparable Interface
    int CompareTo(const Enum &other) const
    {
        auto result{ *this <=> other };

        if ( result == std::strong_ordering::less )
            return -1;
        else if ( result == std::strong_ordering::equal )
            return 0;
        else
            return 1;
    }

    // IConvertible Interface
    TypeCode GetTypeCode() const
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

    bool ToBoolean() const { return _currentValue; }

    std::byte ToByte() const { return std::byte{_currentValue}; }

    char ToChar() const { return {_currentValue}; }

    std::int16_t ToInt16() const { return {_currentValue}; }
    std::int32_t ToInt32() const { return {_currentValue}; }
    std::int64_t ToInt64() const { return {_currentValue}; }

    std::uint16_t ToUInt16() const { return {_currentValue}; }
    std::uint32_t ToUInt32() const { return {_currentValue}; }
    std::uint64_t ToUInt64() const { return {_currentValue}; }

    float  ToSingle() const { return static_cast<float>(_currentValue); }
    double ToDouble() const { return static_cast<double>(_currentValue); }

    std::string ToString() const { return std::string{ GetName() }; }

    // C++ specific stuff.
    // NOTE: We need the <=> AND == operators ONLY, if we want all the other relational
    //       operators to be generated automatically for us.
    constexpr std::strong_ordering operator <=>(const Enum &other) const { return _currentValue <=> other._currentValue; }
    constexpr std::strong_ordering operator <=>(const typename EnumPolicy::value_type other) const { return _currentValue <=> other; }

    constexpr bool operator ==(const Enum &other) const { return _currentValue == other._currentValue; }
    constexpr bool operator ==(const typename EnumPolicy::value_type other) const { return _currentValue == other; }
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

    static typename EnumPolicy::value_type ParseCommon(std::string_view value_string)
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

    // Hidden Friends
    friend bool operator ==(const typename EnumPolicy::value_type left, const Enum<EnumPolicy> &right)
    {
        return left == std::int32_t(right);
    }
};

}

export
template <class T>
struct std::formatter<System::Enum<T>>
{
    // Use {} to print the string form (default)
    // Use {:s} to print the string form and forward to the standard string formatting
    // Use {:i} to print the integer value and forward to the standard integer formatting
    using int_fmt         = std::formatter<int>;
    using string_view_fmt = std::formatter<std::string_view>;
    using underlying_formatter_type = std::variant<string_view_fmt, int_fmt>;

    constexpr auto parse(std::format_parse_context &ctx)
    {
        auto fmt_end = std::find( ctx.begin(), ctx.end(), '}' );

        if ( fmt_end != ctx.begin() )
        {
            // The FIRST character tells us how to format it
            char representation = *ctx.begin();

            if ( representation == 's' )
            {
                ctx.advance_to( std::next( ctx.begin() ) );
                underlying_formatter = string_view_fmt{};
                return std::get<string_view_fmt>(underlying_formatter).parse(ctx);
            }
            else if ( representation == 'i' )
            {
                ctx.advance_to( std::next( ctx.begin() ) );
                underlying_formatter = int_fmt{};
                return std::get<int_fmt>(underlying_formatter).parse(ctx);
            }
        }

        return fmt_end;
    }

    template <typename FormatContext>
    auto format(const System::Enum<T> &object, FormatContext &ctx) const
    {
        if ( std::holds_alternative<int_fmt>(underlying_formatter) )
        {
            ctx.advance_to( std::get<int_fmt>(underlying_formatter).format( static_cast<int>(object), ctx) );
        }
        else if ( std::holds_alternative<string_view_fmt>(underlying_formatter) )
        {
            std::string buffer;

            buffer.append( object.GetName() );
            ctx.advance_to( std::get<string_view_fmt>(underlying_formatter).format(buffer, ctx) );
        }
        return ctx.out();
    }

protected:
    underlying_formatter_type underlying_formatter{ string_view_fmt{} };
};
