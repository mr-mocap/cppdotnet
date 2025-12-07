#pragma once

#include <cppdotnet/System/Xml/XmlNode.hpp>

namespace System::Xml
{

class XmlLinkedNode : public XmlNode
{
public:
    XmlLinkedNode();
    XmlLinkedNode(const XmlLinkedNode &other);
    XmlLinkedNode(XmlLinkedNode &&other);
   ~XmlLinkedNode() override = default;

    XmlLinkedNode &operator =(const XmlLinkedNode &other);
    XmlLinkedNode &operator =(XmlLinkedNode &&other);

    virtual std::shared_ptr<XmlNode> NextSibling() const override;

    virtual std::shared_ptr<XmlNode> PreviousSibling() const override;

protected:
    XmlLinkedNode(std::shared_ptr<XmlNodeList> specific_children_object);
    XmlLinkedNode(std::shared_ptr<XmlNodeList> specific_children_object, std::string_view local_name, std::string_view name);
    XmlLinkedNode(std::shared_ptr<XmlNodeList> specific_children_object,
                  std::string_view             local_name,
                  std::string_view             name,
                  std::string_view             namespace_uri,
                  std::string_view             prefix,
                  std::shared_ptr<XmlDocument> owner_document);
};

}