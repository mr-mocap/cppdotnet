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

namespace System
{

template <>
struct EnumPolicy<System::Xml::XmlNodeType> : EnumTraitTypes<System::Xml::XmlNodeType>
{
    static constexpr std::string_view EnumName = "XmlNodeType";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",                  System::Xml::XmlNodeType::None                  },
            { "Element",               System::Xml::XmlNodeType::Element               },
            { "Attribute",             System::Xml::XmlNodeType::Attribute             },
            { "Text",                  System::Xml::XmlNodeType::Text                  },
            { "CDATA",                 System::Xml::XmlNodeType::CDATA                 },
            { "EntityReference",       System::Xml::XmlNodeType::EntityReference       },
            { "Entity",                System::Xml::XmlNodeType::Entity                },
            { "ProcessingInstruction", System::Xml::XmlNodeType::ProcessingInstruction },
            { "Comment",               System::Xml::XmlNodeType::Comment               },
            { "Document",              System::Xml::XmlNodeType::Document              },
            { "DocumentType",          System::Xml::XmlNodeType::DocumentType          },
            { "DocumentFragment",      System::Xml::XmlNodeType::DocumentFragment      },
            { "Notation",              System::Xml::XmlNodeType::Notation              },
            { "Whitespace",            System::Xml::XmlNodeType::Whitespace            },
            { "SignificantWhitespace", System::Xml::XmlNodeType::SignificantWhitespace },
            { "EndElement",            System::Xml::XmlNodeType::EndElement            },
            { "EndEntity",             System::Xml::XmlNodeType::EndEntity             },
            { "XmlDeclaration",        System::Xml::XmlNodeType::XmlDeclaration        }
        };
};

}