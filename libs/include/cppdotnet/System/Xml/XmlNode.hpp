#pragma once

#include <cppdotnet/System/Nullable.hpp>
#include <cppdotnet/System/Xml/XmlNodeType.hpp>
#include <cppdotnet/System/Xml/XmlAttributeCollection.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>
#include <string>
#include <string_view>
#include <memory>

namespace System::Xml
{

class XmlNode;
class XmlDocument;
class XmlNodeList;
class XmlWriter;

class XmlNode : public std::enable_shared_from_this<XmlNode>
{
public:
    XmlNode() = delete;
    virtual ~XmlNode() = default;

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

    virtual std::string_view LocalName() const = 0;
    virtual std::string_view Name() const = 0;
    virtual std::string_view NamespaceURI() const = 0;

    virtual std::shared_ptr<XmlNode> NextSibling() const;

    XmlNodeType NodeType() const
    {
        XmlNodeType type = _getNodeType();

        POSTCONDITION( type != XmlNodeType::EndElement );
        POSTCONDITION( type != XmlNodeType::EndEntity  );
        POSTCONDITION( type != XmlNodeType::None       );

        return type;
    }

    virtual std::shared_ptr<XmlDocument> OwnerDocument() const = 0;

    virtual Nullable<std::string> Value() const;
            void                  Value(std::nullopt_t new_value_that_is_null)
            {
                Value( Nullable<std::string>{ new_value_that_is_null } );
            }
            void                  Value(std::string_view new_value)
            {
                Value( Nullable<std::string>{ std::string(new_value) } );
            }
            void                  Value(const char *new_value)
            {
                Value( std::string_view( new_value ) );
            }

    virtual std::shared_ptr<XmlNode> ParentNode() const;

    virtual std::string_view Prefix() const = 0;
    virtual             void Prefix(std::string_view new_prefix) = 0;

    virtual std::shared_ptr<XmlNode> PreviousSibling() const;

    virtual void RemoveAll() = 0;

    virtual std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) = 0;

    virtual std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) = 0;

    virtual void WriteTo(XmlWriter &xml_writer) const = 0;
protected:
    XmlAttributeCollection       _attributes;
    std::shared_ptr<XmlNodeList> _children;

    XmlNode(std::shared_ptr<XmlNodeList> specific_children_object);

    virtual XmlNodeType _getNodeType() const = 0;
    virtual bool _thisNodeCanHaveChildren() const;
    virtual bool _canAddAsChild(std::shared_ptr<XmlNode> new_child) const;
    virtual void Value(Nullable<std::string> s);

    bool _isFromSameDocument(std::shared_ptr<XmlNode> node);
};

}