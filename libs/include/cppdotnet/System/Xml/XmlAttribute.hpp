#pragma once

#include <cppdotnet/System/Xml/XmlNode.hpp>

namespace System::Xml
{

class XmlDocument;

class XmlAttribute : public XmlNode
{
public:
    XmlAttribute(std::string_view prefix, std::string_view local_name, std::string_view namespace_uri, std::shared_ptr<XmlDocument> document);
    XmlAttribute(const XmlAttribute &other);
    XmlAttribute(XmlAttribute &&other);
   ~XmlAttribute() override = default;

    XmlAttribute &operator =(const XmlAttribute &other);
    XmlAttribute &operator =(XmlAttribute &&other);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;

    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

    Nullable<std::string> Value() const override;

    void WriteTo(XmlWriter &xml_writer) const override;
protected:
    std::string _value;

    XmlNodeType _getNodeType() const override;
    bool        _thisNodeCanHaveChildren() const override;
    void        Value(Nullable<std::string> new_value) override;
};

}