#pragma once

#include <type_traits>
#include <utility>
#include <string_view>
#include <span>
#include <ranges>
#include <format>
#include <algorithm>

namespace System
{

template <class T>
    requires std::is_enum_v<T>
struct EnumTraitTypes
{
    using value_type           = T;
    using underlying_type      = std::underlying_type_t<T>;
    using name_value_pair_type = std::pair<const std::string_view, const T>;
};

template <class T>
    requires std::is_enum_v<T>
struct EnumTraits
{
    using value_type           = T;
    using underlying_type      = std::underlying_type_t<T>;
    using name_value_pair_type = std::pair<const std::string_view, const T>;

    static auto EnumName() -> const std::string_view { return { }; }

    static std::span<name_value_pair_type> NameValuePairs()
    {
        return {};
    }

    static auto Count() -> std::size_t { return 0; }

    static auto Names() -> std::ranges::keys_view<std::span<name_value_pair_type>>
    {
        return std::views::keys( NameValuePairs() );
    }

    static auto Values() -> std::ranges::values_view<std::span<name_value_pair_type>>
    {
        return std::views::values( NameValuePairs() );
    }

    static auto ValuesAsUnderlyingType()
    {
        auto transform_fn = [=](const value_type item) { return static_cast<underlying_type>(item); };

        return Values() | std::views::transform( transform_fn );
    }

    static auto ToName(value_type value) -> const std::string_view
    {
        auto found = std::ranges::find( NameValuePairs(),
                                        value,
                                        &name_value_pair_type::second
                                      );

        if ( found == NameValuePairs().end() )
            return {};

        return found->first;
    }

    static constexpr value_type min() { return value_type{}; }
    static constexpr value_type max() { return value_type{}; }
};

template <class T>
    requires std::is_enum_v<T>
struct EnumFormatter
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