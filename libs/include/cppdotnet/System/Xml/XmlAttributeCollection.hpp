#pragma once

#include <cppdotnet/System/Xml/XmlNamedNodeMap.hpp>
#include <cppdotnet/System/Collections/Generic/List.hpp>

namespace System::Xml
{

class XmlAttributeCollection : public XmlNamedNodeMap
{
public:
    XmlAttributeCollection() = default;
   ~XmlAttributeCollection() override = default;

    size_t Count() const override;
    
    const std::shared_ptr<XmlNode> GetNamedItem(std::string_view name) const override;
          std::shared_ptr<XmlNode> GetNamedItem(std::string_view name) override;

    std::shared_ptr<XmlNode> SetNamedItem(std::shared_ptr<XmlNode> node) override;

    std::shared_ptr<XmlNode> RemoveNamedItem(std::string_view name) override;

    std::shared_ptr<XmlNode> RemoveAt(int index);

    void RemoveAll();

    const std::shared_ptr<XmlNode> Item(size_t index) const override;
          std::shared_ptr<XmlNode> Item(size_t index) override;
    const std::shared_ptr<XmlNode> Item(int index) const override;
          std::shared_ptr<XmlNode> Item(int index) override;
protected:
    System::Collections::Generic::List<std::shared_ptr<XmlNode>> _nodes;
};

}