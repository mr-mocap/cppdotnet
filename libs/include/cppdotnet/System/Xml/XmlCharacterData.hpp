#pragma once

#include <cppdotnet/System/Xml/XmlLinkedNode.hpp>

namespace System::Xml
{

class XmlCharacterData : public XmlLinkedNode
{
public:
    XmlCharacterData() = delete;
   ~XmlCharacterData() override = default;

    virtual void AppendData(std::string_view data);

    std::shared_ptr<XmlDocument> OwnerDocument() const override;

    Nullable<std::string> Value() const override;

protected:
    Nullable<std::string>        _value;
    std::shared_ptr<XmlDocument> _owner_document;

    XmlCharacterData(std::string_view data, std::shared_ptr<XmlDocument> doc);

    void Value(Nullable<std::string> new_value) override;
};

}