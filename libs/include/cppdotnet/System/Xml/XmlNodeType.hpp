#pragma once

#include <cppdotnet/System/Private/enum.hpp>

namespace System::Xml {

enum class NodeType
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
struct EnumPolicy<System::Xml::NodeType> : EnumTraitTypes<System::Xml::NodeType>
{
    static constexpr std::string_view EnumName = "NodeType";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",                  NodeType::None                  },
            { "Element",               NodeType::Element               },
            { "Attribute",             NodeType::Attribute             },
            { "Text",                  NodeType::Text                  },
            { "CDATA",                 NodeType::CDATA                 },
            { "EntityReference",       NodeType::EntityReference       },
            { "Entity",                NodeType::Entity                },
            { "ProcessingInstruction", NodeType::ProcessingInstruction },
            { "Comment",               NodeType::Comment               },
            { "Document",              NodeType::Document              },
            { "DocumentType",          NodeType::DocumentType          },
            { "DocumentFragment",      NodeType::DocumentFragment      },
            { "Notation",              NodeType::Notation              },
            { "Whitespace",            NodeType::Whitespace            },
            { "SignificantWhitespace", NodeType::SignificantWhitespace },
            { "EndElement",            NodeType::EndElement            },
            { "EndEntity",             NodeType::EndEntity             },
            { "XmlDeclaration",        NodeType::XmlDeclaration        }
        };
};

}