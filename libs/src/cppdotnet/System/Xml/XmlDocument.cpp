#include <cppdotnet/System/Xml/XmlDocument.hpp>

namespace System::Xml
{

XmlNodeType XmlDocument::_getNodeType() const
{
    return XmlNodeType::Document;
}

}