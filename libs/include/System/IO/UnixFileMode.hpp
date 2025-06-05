#pragma once

#include "System/Private/enum.hpp"


namespace System::IO
{

enum class UnixFileMode
{
    None          = 0,    ///@< No Permissions
    OtherExecute  = 1,    ///@< Execute permission for others
    OtherWrite    = 2,    ///@< Write permission for others
    OtherRead     = 4,    ///@< Read permission for others
    GroupExecute  = 8,    ///@< Execute permission for group
    GroupWrite    = 16,   ///@< Write permission for group
    GroupRead     = 32,   ///@< Read permission for group
    UserExecute   = 64,   ///@< Execute permission for user
    UserWrite     = 128,  ///@< Write permission for user
    UserRead      = 256,  ///@< Read permission for user
    StickyBit     = 512,  ///@< Sticky bit permission
    SetGroup      = 1024, ///@< Set group permission
    SetUser       = 2048  ///@< Set user permission
};

}

namespace System
{

template <>
struct EnumTraits<IO::UnixFileMode> : EnumTraitTypes<IO::UnixFileMode>
{
    static auto EnumName() -> std::string_view { return "UnixFileMode"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",         IO::UnixFileMode::None },
            { "OtherExecute", IO::UnixFileMode::OtherExecute },
            { "OtherWrite",   IO::UnixFileMode::OtherWrite },
            { "OtherRead",    IO::UnixFileMode::OtherRead },
            { "GroupExecute", IO::UnixFileMode::GroupExecute },
            { "GroupWrite",   IO::UnixFileMode::GroupWrite },
            { "GroupRead",    IO::UnixFileMode::GroupRead },
            { "UserExecute",  IO::UnixFileMode::UserExecute },
            { "UserWrite",    IO::UnixFileMode::UserWrite },
            { "UserRead",     IO::UnixFileMode::UserRead },
            { "StickyBit",    IO::UnixFileMode::StickyBit },
            { "SetGroup",     IO::UnixFileMode::SetGroup },
            { "SetUser",      IO::UnixFileMode::SetUser }
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

    static constexpr value_type min() { return IO::UnixFileMode::None; }
    static constexpr value_type max() { return IO::UnixFileMode::SetUser; }
};

}