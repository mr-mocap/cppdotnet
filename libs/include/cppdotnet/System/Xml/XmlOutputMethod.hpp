#pragma once

#include <cppdotnet/System/Private/enum.hpp>

namespace System::Xml
{

enum class XmlOutputMethod
{
    Xml,        ///@< Serialize according to the XML 1.0 rules
    Html,       ///@< Serialize according to the HTML rules specified by XSLT
    Text,       ///@< Serialize text blocks only
    AutoDetect  ///@< Use the XSLT rules to choose between the Xml and Html output methods at runtime
};

}

namespace System
{

template <>
struct EnumPolicy<System::Xml::XmlOutputMethod> : EnumTraitTypes<System::Xml::XmlOutputMethod>
{
    static constexpr std::string_view EnumName = "XmlOutputMethod";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Xml",        Xml::XmlOutputMethod::Xml        },
            { "Html",       Xml::XmlOutputMethod::Html       },
            { "Text",       Xml::XmlOutputMethod::Text       },
            { "AutoDetect", Xml::XmlOutputMethod::AutoDetect }
        };
};

}