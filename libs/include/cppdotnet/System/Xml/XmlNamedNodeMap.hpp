#pragma once

#include <cstddef>
#include <memory>

namespace System::Xml
{

class XmlNode;

class XmlNamedNodeMap
{
public:
    virtual ~XmlNamedNodeMap() = default;

    virtual size_t Count() const = 0;
    
    virtual std::shared_ptr<XmlNode> GetNamedItem(std::string_view name) const = 0;

    virtual std::shared_ptr<XmlNode> SetNamedItem(std::shared_ptr<XmlNode> node) = 0;

    virtual std::shared_ptr<XmlNode> RemoveNamedItem(std::string_view name) = 0;

    virtual void  RemoveAll();

    virtual std::shared_ptr<XmlNode> Item(size_t index) const = 0;
    virtual std::shared_ptr<XmlNode> Item(int index) const = 0;
};

}