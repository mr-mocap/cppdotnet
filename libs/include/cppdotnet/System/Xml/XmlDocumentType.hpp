#pragma once

#include <cppdotnet/System/Xml/XmlLinkedNode.hpp>

namespace System::Xml
{

class XmlDocumentType : public XmlLinkedNode
{
public:
    XmlDocumentType(std::string_view name, std::shared_ptr<XmlDocument> doc);
    XmlDocumentType(std::string_view name,
                    std::string_view publicId,
                    std::string_view systemId,
                    std::string_view InternalSubset,
                    std::shared_ptr<XmlDocument> doc);
    XmlDocumentType(const XmlDocumentType &other);
    XmlDocumentType(XmlDocumentType &&other);
   ~XmlDocumentType() override = default;

    XmlDocumentType &operator =(const XmlDocumentType &other);
    XmlDocumentType &operator =(XmlDocumentType &&other);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;

    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

    std::string_view InternalSubset() const
    {
        return _internal_subset;
    }

    std::string_view SystemId() const
    {
        return _system_id;
    }

    void WriteTo(XmlWriter &xml_writer) const override;
protected:
    std::string _internal_subset;
    std::string _system_id;

    XmlNodeType _getNodeType() const override;
    bool        _thisNodeCanHaveChildren() const override;
    bool        _canAddAsChild(std::shared_ptr<XmlNode> new_child) const override;
};

}