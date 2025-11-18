#pragma once

#include <cppdotnet/System/Nullable.hpp>
#include <cppdotnet/System/Xml/XmlNodeType.hpp>
#include <cppdotnet/System/Xml/XmlAttributeCollection.hpp>
#include <cppdotnet/System/Private/private.hpp>
#include <string>
#include <string_view>
#include <memory>

namespace System::Xml
{

class XmlNode;
class XmlDocument;
class XmlNodeList;

class XmlNode : public std::enable_shared_from_this<XmlNode>
{
public:
    XmlNode() = delete;
    virtual ~XmlNode() = default;

    virtual std::shared_ptr<XmlNode> AppendChild(std::shared_ptr<XmlNode> new_child);
    virtual std::shared_ptr<XmlNode> PrependChild(std::shared_ptr<XmlNode> new_child);

    virtual std::shared_ptr<XmlAttributeCollection> Attributes() const;
    
    virtual std::shared_ptr<XmlNode> Clone() const;
    virtual std::shared_ptr<XmlNode> CloneNode(bool deep) const = 0;

    virtual const XmlNodeList &ChildNodes() const;
    virtual       XmlNodeList &ChildNodes();

    virtual std::shared_ptr<const XmlNode> FirstChild() const;
    virtual std::shared_ptr<XmlNode> FirstChild();

    virtual std::shared_ptr<const XmlNode> LastChild() const;
    virtual std::shared_ptr<XmlNode> LastChild();

    virtual bool HasChildNodes() const;

    virtual bool IsReadOnly() const;

    virtual std::shared_ptr<XmlNode> InsertAfter(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> ref_child);
    virtual std::shared_ptr<XmlNode> InsertBefore(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> ref_child);

    virtual std::string_view LocalName() const = 0;
    virtual std::string_view Name() const = 0;
    virtual std::string_view NamespaceURI() const = 0;
#if 0
    virtual std::shared_ptr<XmlNode> NextSibling() const = 0;
#endif
    XmlNodeType NodeType() const
    {
        XmlNodeType type = _getNodeType();

        POSTCONDITION( type != XmlNodeType::EndElement );
        POSTCONDITION( type != XmlNodeType::EndEntity  );
        POSTCONDITION( type != XmlNodeType::None       );

        return type;
    }

    virtual std::shared_ptr<XmlDocument> OwnerDocument() const = 0;

    virtual Nullable<std::string> Value() const = 0;

    virtual std::shared_ptr<XmlNode> ParentNode() const;

    virtual std::string_view Prefix() const = 0;
    virtual             void Prefix(std::string_view new_prefix) = 0;
#if 0
    virtual std::shared_ptr<XmlNode> PreviousSibling() const = 0;
#endif

    virtual void RemoveAll() = 0;

    virtual std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) = 0;

    virtual std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) = 0;
protected:
    std::shared_ptr<XmlNodeList> _children;

    XmlNode(std::shared_ptr<XmlNodeList> specific_children_object);

    virtual XmlNodeType _getNodeType() const = 0;
};

}