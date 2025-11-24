#pragma once

#include <cppdotnet/System/Xml/XmlCharacterData.hpp>

namespace System::Xml
{

class XmlText : public XmlCharacterData
{
public:
    XmlText(std::string_view data, std::shared_ptr<XmlDocument> doc);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    std::string_view LocalName() const override;
    std::string_view Name() const override;
    std::string_view NamespaceURI() const override;

    std::string_view Prefix() const override;
                void Prefix(std::string_view new_prefix) override;

    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;

    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

    void WriteTo(XmlWriter &xml_writer) const override;
protected:
    std::string _prefix;
    std::string _local_name;
    std::string _namespace_uri;

    XmlNodeType _getNodeType() const override;
};

}