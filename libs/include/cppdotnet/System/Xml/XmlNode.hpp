#pragma once

#include <cppdotnet/System/Nullable.hpp>
#include <cppdotnet/System/Xml/XmlNodeType.hpp>
#include <cppdotnet/System/Xml/XmlAttributeCollection.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>
#include <string>
#include <string_view>
#include <memory>
#include <concepts>

namespace System::Xml
{

class XmlNode;
class XmlDocument;
class XmlNodeList;
class XmlWriter;

class XmlNode : public std::enable_shared_from_this<XmlNode>
{
public:
    XmlNode() = default;
    XmlNode(const XmlNode &other);
    XmlNode(XmlNode &&other);
    virtual ~XmlNode() = default;

    XmlNode &operator =(const XmlNode &other);
    XmlNode &operator =(XmlNode &&other);

    // Allow treating std::shared_ptr like a normal point and allow auto-cast to base class type
    template<std::derived_from<XmlNode> NodeType>
    std::shared_ptr<NodeType> AppendChild(std::shared_ptr<NodeType> new_child)
    {
        // Call the virtual method with the base class type (XmlNode)
        return std::static_pointer_cast<NodeType>( AppendChild( std::static_pointer_cast<XmlNode>( new_child ) ) );
    }

    virtual std::shared_ptr<XmlNode> AppendChild(std::shared_ptr<XmlNode> new_child);
    virtual std::shared_ptr<XmlNode> PrependChild(std::shared_ptr<XmlNode> new_child);

    const XmlAttributeCollection &Attributes() const;
          XmlAttributeCollection &Attributes();
    
    virtual std::shared_ptr<XmlNode> Clone() const;

    virtual std::shared_ptr<XmlNode> CloneNode(bool deep) const = 0;

    virtual XmlNodeList &ChildNodes() const;

    virtual std::shared_ptr<XmlNode> FirstChild() const;

    virtual std::shared_ptr<XmlNode> LastChild() const;

    virtual bool HasChildNodes() const;

    virtual bool IsReadOnly() const;

    virtual std::shared_ptr<XmlNode> InsertAfter(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> ref_child);
    virtual std::shared_ptr<XmlNode> InsertBefore(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> ref_child);

    virtual std::string_view LocalName() const;
    virtual std::string_view Name() const;
    virtual std::string_view NamespaceURI() const;

    virtual std::shared_ptr<XmlNode> NextSibling() const;

    XmlNodeType NodeType() const
    {
        XmlNodeType type = _getNodeType();

        POSTCONDITION( type != XmlNodeType::EndElement );
        POSTCONDITION( type != XmlNodeType::EndEntity  );
        POSTCONDITION( type != XmlNodeType::None       );

        return type;
    }

    virtual std::string_view OuterXml() const;

    virtual std::shared_ptr<XmlDocument> OwnerDocument() const;

    virtual std::string_view Value() const;
            
    void Value(const char *new_value)
    {
        if ( new_value )
            Value( std::string_view( new_value ) );
        else
            Value( std::string_view() );  // We can't construct a std::string_view(nullptr)
    }

    virtual void Value(std::string_view new_value);

    virtual std::shared_ptr<XmlNode> ParentNode() const;

    virtual std::string_view Prefix() const;
    virtual             void Prefix(std::string_view new_prefix);

    virtual std::shared_ptr<XmlNode> PreviousSibling() const;

    virtual void RemoveAll() = 0;

    virtual std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) = 0;

    virtual std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) = 0;

    virtual void WriteTo(XmlWriter &xml_writer) const = 0;
protected:
    XmlAttributeCollection       _attributes;
    std::shared_ptr<XmlNodeList> _children;
    std::string                  _local_name;
    std::string                  _name;
    std::string                  _namespace_uri;
    std::string                  _outer_xml;
    std::string                  _prefix;
    std::shared_ptr<XmlDocument> _owner_document;

    struct NodeConstructionParameters
    {
        std::string_view local_name;
        std::string_view name;
        std::string_view namespace_uri;
        std::string      outer_xml;
        std::string_view prefix;
        std::shared_ptr<XmlDocument> owner_document;
    };

    XmlNode(std::shared_ptr<XmlNodeList> specific_children_object);
    XmlNode(std::shared_ptr<XmlNodeList> specific_children_object, std::string_view local_name, std::string_view name);
    XmlNode(std::shared_ptr<XmlNodeList> specific_children_object,
            std::string_view local_name,
            std::string_view name,
            std::string_view namespace_uri,
            std::string_view prefix,
            std::shared_ptr<XmlDocument> owner_document);
    XmlNode(std::shared_ptr<XmlNodeList> specific_children_object, NodeConstructionParameters &&parameters);

    virtual XmlNodeType _getNodeType() const = 0;
    virtual bool _thisNodeCanHaveChildren() const;
    virtual bool _canAddAsChild(std::shared_ptr<XmlNode> new_child) const;

    bool _isFromSameDocument(std::shared_ptr<XmlNode> node);
};

}