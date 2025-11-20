#pragma once

#include <cppdotnet/System/Private/enum.hpp>

namespace System::Xml
{

enum class Formatting
{
    None,       ///@< No special formatting is applied (default)
    Indented    ///@< Causes child elements to be indented according to the @c Indentation and @c IndentChar settings
};

}

namespace System
{

template <>
struct EnumPolicy<System::Xml::Formatting> : EnumTraitTypes<System::Xml::Formatting>
{
    static constexpr std::string_view EnumName = "Formatting";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",     System::Xml::Formatting::None     },
            { "Indented", System::Xml::Formatting::Indented }
        };
};

}