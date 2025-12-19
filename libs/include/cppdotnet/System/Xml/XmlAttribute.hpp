#pragma once

#include <cppdotnet/System/Xml/XmlNode.hpp>

namespace System::Xml
{

class XmlDocument;
class XmlText;

class XmlAttribute : public XmlNode
{
public:
    XmlAttribute() = delete;
    XmlAttribute(std::string_view prefix, std::string_view local_name, std::string_view namespace_uri, std::shared_ptr<XmlDocument> document);
    XmlAttribute(const XmlAttribute &other);
    XmlAttribute(XmlAttribute &&other);
   ~XmlAttribute() override = default;

    XmlAttribute &operator =(const XmlAttribute &other);
    XmlAttribute &operator =(XmlAttribute &&other);

    using XmlNode::AppendChild;
    std::shared_ptr<XmlText> AppendChild(std::shared_ptr<XmlText> new_child);

    using XmlNode::PrependChild;
    std::shared_ptr<XmlText> PrependChild(std::shared_ptr<XmlText> new_child);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;

    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

    std::string_view Value() const override;
    void             Value(std::string_view new_value) override;

    void WriteTo(XmlWriter &xml_writer) const override;
protected:
    std::string _value;

    XmlNodeType _getNodeType() const override;
    bool        _canAddAsChild(std::shared_ptr<XmlNode> new_child) const override;
    bool        _thisNodeCanHaveChildren() const override;
    void        _clearValue();
    void        _updateValue(std::string_view new_value);
};

}