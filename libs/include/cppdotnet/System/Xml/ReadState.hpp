#pragma once

#include <cppdotnet/System/Private/enum.hpp>

namespace System::Xml {

enum class ReadState
{
    Initial     = 0,
    Interactive = 1,
    Error       = 2,
    EndOfFile   = 3,
    Closed      = 4
};

}

namespace System::Xml
{

template <>
struct EnumPolicy<System::Xml::ReadState> : EnumTraitTypes<System::Xml::ReadState>
{
    static constexpr std::string_view EnumName = "ReadState";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Initial",     ReadState::Initial     },
            { "Interactive", ReadState::Interactive },
            { "Error",       ReadState::Error       },
            { "EndOfFile",   ReadState::EndOfFile   },
            { "Closed",      ReadState::Closed      }
        };
};

}