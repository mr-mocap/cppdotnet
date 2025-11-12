#pragma once

#include <cppdotnet/System/Nullable.hpp>
#include <cppdotnet/System/Xml/XmlNodeType.hpp>
#include <cppdotnet/System/Private/private.hpp>
#include <string_view>

namespace System::Xml
{

class XmlNode
{
public:
    XmlNode() = default;
    virtual ~XmlNode() = default;

    virtual std::string_view Name() const = 0;

    XmlNodeType NodeType() const
    {
        XmlNodeType type = _getNodeType();

        POSTCONDITION( type != XmlNodeType::EndElement );
        POSTCONDITION( type != XmlNodeType::EndEntity  );
        POSTCONDITION( type != XmlNodeType::None       );

        return type;
    }

    virtual Nullable<std::string> Value() = 0;

protected:
    virtual XmlNodeType _getNodeType() const = 0;
};

}