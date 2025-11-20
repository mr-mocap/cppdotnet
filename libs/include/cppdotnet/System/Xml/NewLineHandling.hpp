#pragma once

#include <cppdotnet/System/Private/enum.hpp>

namespace System::Xml
{

enum class NewLineHandling
{
    Replace,    ///@< New line characters are replaced to match the character specified in the @c NewLineChars property
    Entitize,   ///@< New line characters are entitized.
    None        ///@< The new line characters are unchanged
};

}

namespace System
{

template <>
struct EnumPolicy<System::Xml::NewLineHandling> : EnumTraitTypes<System::Xml::NewLineHandling>
{
    static constexpr std::string_view EnumName = "NewLineHandling";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Replace",  System::Xml::NewLineHandling::Replace  },
            { "Entitize", System::Xml::NewLineHandling::Entitize },
            { "None",     System::Xml::NewLineHandling::None     }
        };
};

}