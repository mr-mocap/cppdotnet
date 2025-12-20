#pragma once

#include <cppdotnet/System/Xml/XmlLinkedNode.hpp>
#include <cppdotnet/System/Xml/XmlAttribute.hpp>

namespace System::Xml
{

class XmlElement : public XmlLinkedNode
{
public:
    XmlElement() = delete;
    XmlElement(std::string_view prefix, std::string_view local_name, std::string_view namespace_uri, std::shared_ptr<XmlDocument> document);
    XmlElement(const XmlElement &other);
    XmlElement(XmlElement &&other);
   ~XmlElement() override = default;

    XmlElement &operator =(const XmlElement &other);
    XmlElement &operator =(XmlElement &&other);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    std::string_view Value() const override;
    using XmlNode::Value;

    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;

    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

    virtual std::shared_ptr<XmlAttribute> GetAttributeNode(std::string_view name) const;
    virtual void                          SetAttributeNode(std::shared_ptr<XmlAttribute> new_attribute);

    virtual std::string_view GetAttribute(std::string_view name) const;
    virtual void             SetAttribute(std::string_view name, std::string_view value);

    virtual void RemoveAttribute(std::string_view name);

    void WriteTo(XmlWriter &xml_writer) const override;
protected:
    std::string _value;

    XmlNodeType _getNodeType() const override;
    bool        _thisNodeCanHaveChildren() const override;
    bool        _canAddAsChild(std::shared_ptr<XmlNode> new_child) const override;

    void _writeAttributes(XmlWriter &xml_writer) const;
    void _writeChildren(XmlWriter &xml_writer) const;
    void _clearValue();
    void _updateValue(std::string_view new_value);
    void _updateOuterXml();
    std::string _generateValue() const;
};

}