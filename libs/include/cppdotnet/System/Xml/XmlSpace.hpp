#pragma once

#include <cppdotnet/System/Private/enum.hpp>

namespace System::Xml
{

enum class XmlSpace
{
    None,       ///@< No @c xml:space scope
    Default,    ///@< The @c xml:space scope equals @c default
    Preserve    ///@< The @c xml:space scope equals @c preserve
};

}

namespace System
{

template <>
struct EnumPolicy<System::Xml::XmlSpace> : EnumTraitTypes<System::Xml::XmlSpace>
{
    static constexpr std::string_view EnumName = "XmlSpace";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",     System::Xml::XmlSpace::None     },
            { "Default",  System::Xml::XmlSpace::Default  },
            { "Preserve", System::Xml::XmlSpace::Preserve }
        };
};

}