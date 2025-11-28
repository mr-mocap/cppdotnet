#pragma once

#include <cppdotnet/System/Xml/XmlLinkedNode.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>

namespace System::Xml
{

class XmlDeclaration : public XmlLinkedNode
{
public:
    XmlDeclaration();
    XmlDeclaration(std::string_view version, std::shared_ptr<XmlDocument> document);
    XmlDeclaration(std::string_view version, std::string_view encoding, std::shared_ptr<XmlDocument> document);
    XmlDeclaration(std::string_view version, std::string_view encoding, std::string_view standalone, std::shared_ptr<XmlDocument> document);
    XmlDeclaration(const XmlDeclaration &other);
   ~XmlDeclaration() override = default;

    XmlDeclaration &operator =(const XmlDeclaration &other);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    std::string_view LocalName() const override;
    std::string_view Name() const override;
    std::string_view NamespaceURI() const override;

    std::shared_ptr<XmlDocument> OwnerDocument() const override;

    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;

    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

    std::string_view Prefix() const override;
                void Prefix(std::string_view new_prefix) override;

    std::string_view Version() const
    {
        return _version;
    }

    std::string_view Encoding() const
    {
        return _encoding;
    }

    std::string_view Standalone() const
    {
        return _standalone;
    }

    Nullable<std::string> Value() const override;

    void WriteTo(XmlWriter &xml_writer) const override;
protected:
    std::string                  _version{ "1.0" };
    std::string                  _encoding;
    std::string                  _standalone;
    std::shared_ptr<XmlDocument> _owner_document;
    std::string                  _value;

    XmlNodeType _getNodeType() const override;
};

}