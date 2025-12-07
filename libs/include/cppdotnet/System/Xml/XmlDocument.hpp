#pragma once

#include <cppdotnet/System/Xml/XmlNode.hpp>
#include <cppdotnet/System/Xml/XmlNameTable.hpp>
#include <cppdotnet/System/Xml/XmlImplementation.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>
#include <memory>

namespace System::Xml
{

class XmlAttribute;
class XmlElement;
class XmlText;
class XmlComment;
class XmlDeclaration;
class XmlProcessingInstruction;

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

    virtual std::shared_ptr<XmlAttribute> CreateAttribute(std::string_view local_name,
                                                          std::string_view namespace_uri);

    virtual std::shared_ptr<XmlAttribute> CreateAttribute(std::string_view prefix,
                                                          std::string_view local_name,
                                                          std::string_view namespace_uri);

    virtual std::shared_ptr<XmlElement>   CreateElement(std::string_view name);

    virtual std::shared_ptr<XmlElement>   CreateElement(std::string_view local_name,
                                                        std::string_view namespace_uri);

    virtual std::shared_ptr<XmlElement>   CreateElement(std::string_view prefix,
                                                        std::string_view local_name,
                                                        std::string_view namespace_uri);

    virtual std::shared_ptr<XmlText> CreateTextNode(std::string_view text);

    virtual std::shared_ptr<XmlDeclaration> CreateXmlDeclaration(std::string_view version);
    virtual std::shared_ptr<XmlDeclaration> CreateXmlDeclaration(std::string_view version,
                                                                 std::string_view encoding);
    virtual std::shared_ptr<XmlDeclaration> CreateXmlDeclaration(std::string_view version,
                                                                 std::string_view encoding,
                                                                 std::string_view standalone);

    virtual std::shared_ptr<XmlProcessingInstruction> CreateProcessingInstruction(std::string_view target);
    virtual std::shared_ptr<XmlProcessingInstruction> CreateProcessingInstruction(std::string_view target, std::string_view data);

    virtual std::shared_ptr<XmlComment> CreateComment(std::string_view data);

    XmlNameTable &NameTable() const
    {
        INVARIANT( _implementation );

        return *_implementation->NameTable();
    }

    std::shared_ptr<XmlImplementation> Implementation() const;

    std::string_view LocalName() const override;
    std::string_view Name() const override;
    std::string_view NamespaceURI() const override;

    std::shared_ptr<XmlDocument> OwnerDocument() const override;

    std::string_view Prefix() const override;
                void Prefix(std::string_view new_prefix) override;
    
    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;
    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

    void WriteTo(XmlWriter &xml_writer) const override;
protected:
    std::shared_ptr<XmlImplementation> _implementation;

    XmlNodeType _getNodeType() const override;
    bool        _thisNodeCanHaveChildren() const override;
    bool        _canAddAsChild(std::shared_ptr<XmlNode> new_child) const override;

    std::shared_ptr<XmlDocument> _localSharedFromThis();
};

}