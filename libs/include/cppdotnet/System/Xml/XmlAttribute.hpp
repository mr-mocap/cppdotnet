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
   ~XmlAttribute() override = default;

    XmlAttribute &operator =(const XmlAttribute &other);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    std::string_view LocalName() const override;
    std::string_view Name() const override;
    std::string_view NamespaceURI() const override;

    std::shared_ptr<const XmlDocument> OwnerDocument() const override;
    std::shared_ptr<XmlDocument>       OwnerDocument()       override;

    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;

    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

    Nullable<std::string> Value() const override;

    std::string_view Prefix() const override;
                void Prefix(std::string_view new_prefix) override;
protected:
    std::string _prefix;
    std::string _local_name;
    std::string _namespace_uri;
    std::string _value;
    std::shared_ptr<XmlDocument> _owner_document;

    XmlNodeType _getNodeType() const override;
};

}