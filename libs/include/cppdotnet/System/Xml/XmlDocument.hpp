#pragma once

#include <cppdotnet/System/Xml/XmlNode.hpp>
#include <cppdotnet/System/Xml/XmlNameTable.hpp>
#include <cppdotnet/System/Xml/XmlImplementation.hpp>
#include <cppdotnet/System/Private/private.hpp>
#include <memory>

namespace System::Xml
{

class XmlAttribute;

class XmlDocument : public XmlNode
{
public:
    XmlDocument();
    XmlDocument(std::shared_ptr<XmlImplementation> implementation);
    XmlDocument(const XmlNameTable &name_table);
    XmlDocument(std::unique_ptr<XmlNameTable> &&name_table);

    XmlDocument(std::shared_ptr<XmlNameTable> &name_table);
    XmlDocument(const std::shared_ptr<XmlNameTable> &name_table);

    XmlDocument(std::shared_ptr<XmlNameTable> &&name_table);
   ~XmlDocument() override = default;
    
    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    virtual std::shared_ptr<XmlAttribute> CreateAttribute(std::string_view name);

    const XmlNameTable &NameTable() const
    {
        INVARIANT( _implementation );

        return *_implementation->NameTable();
    }

          XmlNameTable &NameTable()
    {
        INVARIANT( _implementation );

        return *_implementation->NameTable();
    }

    std::shared_ptr<const XmlImplementation> Implementation() const;
    std::shared_ptr<XmlImplementation>       Implementation();

    std::string_view LocalName() const override;
    std::string_view Name() const override;
    std::string_view NamespaceURI() const override;

    std::shared_ptr<const XmlDocument> OwnerDocument() const override;
    std::shared_ptr<XmlDocument>       OwnerDocument()       override;

    std::string_view Prefix() const override;
                void Prefix(std::string_view new_prefix) override;
    
    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;
    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

    Nullable<std::string> Value() const override;
protected:
    std::shared_ptr<XmlImplementation> _implementation;

    XmlNodeType _getNodeType() const override;
    std::shared_ptr<XmlDocument> _localSharedFromThis();
};

}