#pragma once

#include <cppdotnet/System/Xml/XmlNode.hpp>

namespace System::Xml
{

class XmlLinkedNode : public XmlNode
{
public:
    XmlLinkedNode() = delete;
   ~XmlLinkedNode() override = default;

    virtual std::shared_ptr<XmlNode> NextSibling() const override;

    virtual std::shared_ptr<XmlNode> PreviousSibling() const override;

protected:
    XmlLinkedNode(std::shared_ptr<XmlNodeList> specific_children_object);
};

}