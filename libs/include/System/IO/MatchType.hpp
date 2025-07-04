#pragma once

namespace System::IO
{

enum class MatchType
{
    Simple,
    Win32
};

}

namespace System
{

template <>
struct EnumPolicy<System::IO::MatchType> : EnumTraitTypes<System::IO::MatchType>
{
public:

    static constexpr std::string_view EnumName = "MatchType";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Simple", IO::MatchType::Simple },
            { "Win32",  IO::MatchType::Win32  }
        };
};

}