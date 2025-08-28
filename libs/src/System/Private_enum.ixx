module;

export module System:Private_enum;

export import <utility>;
export import <string>;
export import <string_view>;
export import <span>;
import <ranges>;
export import <format>;
import <algorithm>;
import <array>;
import <type_traits>;
import <variant>;

namespace System
{

export
template <class T>
    requires std::is_enum_v<T>
struct EnumTraitTypes
{
    using value_type           = T;
    using underlying_type      = std::underlying_type_t<T>;
    using name_value_pair_type = std::pair<std::string_view, T>;
};

export
template <class T>
    requires std::is_enum_v<T>
struct EnumPolicy : EnumTraitTypes<T>
{
public:

    static constexpr std::string_view EnumName = "UndefinedEnumPolicy";

    static constexpr typename EnumTraitTypes<T>::name_value_pair_type NameValueArray[] = {
            { "UndefinedEnumValue", static_cast<T>(0) }
        };
};

export
template <class T, class EnumPolicyT = EnumPolicy<T>>
    requires std::is_enum_v<T>
struct EnumTraits : EnumPolicyT
{
    using value_type           = EnumPolicyT::value_type;
    using underlying_type      = std::underlying_type_t<T>;
    using name_value_pair_type = EnumPolicyT::name_value_pair_type;

    using name_array_type      = std::ranges::keys_view<std::span<name_value_pair_type>>;
    using value_array_type     = std::ranges::values_view<std::span<name_value_pair_type>>;

    static constexpr auto NameValuePairs() -> decltype( std::span{ EnumPolicyT::NameValueArray } )
    {
        return std::span{ EnumPolicyT::NameValueArray };
    }

    static constexpr std::size_t Count() { return NameValuePairs().size(); }

    static constexpr auto Names() -> name_array_type
    {
        return std::views::keys( NameValuePairs() );
    }

    static constexpr auto Values() -> value_array_type
    {
        return std::views::values( NameValuePairs() );
    }

    static constexpr auto ValuesAsUnderlyingType()
    {
        auto transform_fn = [=](const value_type item) { return static_cast<underlying_type>(item); };

        return Values() | std::views::transform( transform_fn );
    }

    static constexpr bool IsDefined(value_type value)
    {
        return std::ranges::find( NameValuePairs(),
                                  value,
                                  &name_value_pair_type::second
                                ) != NameValuePairs().end();
    }

    static constexpr bool IsDefined(underlying_type value)
    {
        return IsDefined( static_cast<value_type>(value) );
    }

    static constexpr bool IsDefined(std::string_view value_string)
    {
        return std::ranges::find( NameValuePairs(),
                                  value_string,
                                  &name_value_pair_type::first
                                ) != NameValuePairs().end();
    }

    static constexpr auto ToName(value_type value) -> std::string_view
    {
        auto found = std::ranges::find( NameValuePairs(),
                                        value,
                                        &name_value_pair_type::second
                                      );

        if ( found == NameValuePairs().end() )
            return {};

        return found->first;
    }

    static constexpr auto ToName(underlying_type value) -> std::string_view
    {
        return ToName( static_cast<value_type>(value) );
    }

    static constexpr value_type Min() { return NameValuePairs().front(); }
    static constexpr value_type Max() { return NameValuePairs().back(); }
};

export
template <class T>
    requires std::is_enum_v<T>
struct EnumFormatter
{
    // Use {} to print the string form (default)
    // Use {:s} to print the string form and forward to the standard string formatting
    // Use {:i} to print the integer value and forward to the standard integer formatting
    using formatter_type  = std::formatter<T>;
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

    auto format(T enum_value, std::format_context &ctx) const
    {
        if ( std::holds_alternative<int_fmt>(underlying_formatter) )
        {
            ctx.advance_to( std::get<int_fmt>(underlying_formatter).format( static_cast<int>(enum_value), ctx) );
        }
        else if ( std::holds_alternative<string_view_fmt>(underlying_formatter) )
        {
            std::string buffer;

            buffer.append( System::EnumTraits<T>::ToName(enum_value) );
            ctx.advance_to( std::get<string_view_fmt>(underlying_formatter).format(buffer, ctx) );
        }
        return ctx.out();
    }

protected:
    underlying_formatter_type underlying_formatter{ string_view_fmt{} };
};

}

export
template <typename T>
requires
requires {
    typename System::EnumFormatter<T>::formatter_type;
}
struct std::formatter<T> : System::EnumFormatter<T>
{
};
