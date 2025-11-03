#pragma once

#include <cppdotnet/System/Xml/XmlNode.hpp>
#include <cppdotnet/System/Xml/XmlNameTable.hpp>

namespace System::Xml
{

class XmlDocument : public XmlNode
{
public:
    XmlDocument() = default;
   ~XmlDocument() = default override;
};

}