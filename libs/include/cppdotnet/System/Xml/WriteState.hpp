#pragma once

#include <cppdotnet/System/Private/enum.hpp>

namespace System::Xml
{

enum class WriteState
{
    Start,      ///@< Indicates that a Write method has not yet been called
    Prolog,     ///@< Indicates that the prolog is being written
    Element,    ///@< Indicates that an element start tag is being written
    Attribute,  ///@< Indicates that an attribute value is being written
    Content,    ///@< Indicates that element content is being written
    Closed,     ///@< Indicates that the @c Close() method has been called
    Error       ///@< An exception has been thrown, which has left the XmlWriter in an invalid state
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