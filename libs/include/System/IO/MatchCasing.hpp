#include "System/Private/enum.hpp"

namespace System::IO
{

enum class MatchCasing
{
    PlatformDefault, ///@< Matches using the default casing for the given platform
    CaseSensitive,   ///@< Matches respecting character casing
    CaseInsensitive  ///@< Matches ignoring character casing
};

}

namespace System
{

template <>
struct EnumPolicy<System::IO::MatchCasing> : EnumTraitTypes<System::IO::MatchCasing>
{
    static constexpr std::string_view EnumName = "MatchCasing";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "PlatformDefault", IO::MatchCasing::PlatformDefault },
            { "CaseSensitive",   IO::MatchCasing::CaseSensitive   },
            { "CaseInsensitive", IO::MatchCasing::CaseInsensitive }
        };
};

}