#pragma once

#include "System/Private/enum.hpp"

namespace System
{

enum class PlatformID
{
    Win32S       = 0,
    Win32Windows = 1,
    Win32NT = 2,
    WinCE   = 3,
    Unix    = 4,
    Xbox    = 5,
    MacOSX  = 6
};

}

namespace System
{

template <>
struct EnumTraits<System::PlatformID> : EnumTraitTypes<System::PlatformID>
{
    static auto EnumName() -> std::string_view { return "PlatformID"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Win32S",       System::PlatformID::Win32S       },
            { "Win32Windows", System::PlatformID::Win32Windows },
            { "Win32NT",      System::PlatformID::Win32NT      },
            { "WinCE",        System::PlatformID::WinCE        },
            { "Unix",         System::PlatformID::Unix         },
            { "Xbox",         System::PlatformID::Xbox         },
            { "MacOSX",       System::PlatformID::MacOSX       }
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

    static constexpr value_type min() { return System::PlatformID::Win32S; }
    static constexpr value_type max() { return System::PlatformID::MacOSX; }
};

}
