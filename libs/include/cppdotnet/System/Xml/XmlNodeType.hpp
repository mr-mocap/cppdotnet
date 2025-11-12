#pragma once

#include <cppdotnet/System/Private/enum.hpp>

namespace System::Xml
{

enum class XmlNodeType
{
    None      = 0,
    Element   = 1,
    Attribute = 2,
    Text      = 3,
    CDATA     = 4,
    EntityReference  = 5,
    Entity    = 6,
    ProcessingInstruction = 7,
    Comment   = 8,
    Document  = 9,
    DocumentType     = 10,
    DocumentFragment = 11,
    Notation   = 12,
    Whitespace = 13,
    SignificantWhitespace = 14,
    EndElement = 15,
    EndEntity  = 16,
    XmlDeclaration   = 17
};

}

namespace System::Xml
{

template <>
struct EnumPolicy<XmlNodeType> : EnumTraitTypes<XmlNodeType>
{
    static constexpr std::string_view EnumName = "XmlNodeType";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",                  XmlNodeType::None                  },
            { "Element",               XmlNodeType::Element               },
            { "Attribute",             XmlNodeType::Attribute             },
            { "Text",                  XmlNodeType::Text                  },
            { "CDATA",                 XmlNodeType::CDATA                 },
            { "EntityReference",       XmlNodeType::EntityReference       },
            { "Entity",                XmlNodeType::Entity                },
            { "ProcessingInstruction", XmlNodeType::ProcessingInstruction },
            { "Comment",               XmlNodeType::Comment               },
            { "Document",              XmlNodeType::Document              },
            { "DocumentType",          XmlNodeType::DocumentType          },
            { "DocumentFragment",      XmlNodeType::DocumentFragment      },
            { "Notation",              XmlNodeType::Notation              },
            { "Whitespace",            XmlNodeType::Whitespace            },
            { "SignificantWhitespace", XmlNodeType::SignificantWhitespace },
            { "EndElement",            XmlNodeType::EndElement            },
            { "EndEntity",             XmlNodeType::EndEntity             },
            { "XmlDeclaration",        XmlNodeType::XmlDeclaration        }
        };
};

}