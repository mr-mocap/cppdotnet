#pragma once

#include <cppdotnet/System/Private/enum.hpp>

namespace System::Xml
{

enum class WriteState
{
    Start,
    Prolog,
    Element,
    Attribute,
    Content,
    Closed,
    Error
};

}

namespace System
{

template <>
struct EnumPolicy<System::Xml::WriteState> : EnumTraitTypes<System::Xml::WriteState>
{
    static constexpr std::string_view EnumName = "WriteState";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Start",     Xml::WriteState::Start     },
            { "Prolog",    Xml::WriteState::Prolog    },
            { "Element",   Xml::WriteState::Element   },
            { "Attribute", Xml::WriteState::Attribute },
            { "Content",   Xml::WriteState::Content   },
            { "Closed",    Xml::WriteState::Closed    },
            { "Error",     Xml::WriteState::Error     }
        };
};

}