#pragma once

namespace System::IO
{

enum class MatchCasing
{
    PlatformDefault, ///@< Matches using the default casing for the given platform
    CaseSensitive,   ///@< Matches respecting character casing
    CaseInsensitive  ///@< Matches ignoring character casing
};

}