#pragma once

#include "System/Private/enum.hpp"


namespace System
{

enum class ConsoleModifiers
{
    None    = 0,
    Alt     = 1, ///@< The left or right ALT modifier key
    Shift   = 2, ///@< The left or right SHIFT modifier key
    Control = 4  ///@< The left or right CTRL modifier key
};

}

namespace System
{

template <>
struct EnumTraits<System::ConsoleModifiers> : EnumTraitTypes<System::ConsoleModifiers>
{
    static auto EnumName() -> std::string_view { return "ConsoleModifiers"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",    System::ConsoleModifiers::None    },
            { "Alt",     System::ConsoleModifiers::Alt     },
            { "Shift",   System::ConsoleModifiers::Shift   },
            { "Control", System::ConsoleModifiers::Control }
        };

    static constexpr auto NameValuePairs() -> std::span<const name_value_pair_type>
    {
        return std::span{ NameValueArray };
    }

    static constexpr auto Count() -> std::size_t { return NameValuePairs().size(); }

    static constexpr auto Names() -> std::ranges::keys_view<std::span<const name_value_pair_type>>
    {
        return std::views::keys( NameValuePairs() );
    }

    static constexpr auto Values() -> std::ranges::values_view<std::span<const name_value_pair_type>>
    {
        return std::views::values( NameValuePairs() );
    }

    static constexpr auto ValuesAsUnderlyingType()
    {
        auto to_underlying_type = [](const value_type item) { return static_cast<underlying_type>(item); };

        return Values() | std::views::transform( to_underlying_type );
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

    static constexpr value_type min() { return System::ConsoleModifiers::None; }
    static constexpr value_type max() { return System::ConsoleModifiers::Control; }
};

}