#pragma once

#include <cppdotnet/System/Xml/XmlCharacterData.hpp>

namespace System::Xml
{

class XmlWhitespace : public XmlCharacterData
{
public:
    XmlWhitespace(std::shared_ptr<XmlDocument> doc);
    XmlWhitespace(std::string_view whitespace, std::shared_ptr<XmlDocument> doc);
    XmlWhitespace(const XmlWhitespace &other);
    XmlWhitespace(XmlWhitespace &&other);
   ~XmlWhitespace() override = default;

    XmlWhitespace &operator =(const XmlWhitespace &other);
    XmlWhitespace &operator =(XmlWhitespace &&other);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    using XmlCharacterData::Value;
    void Value(std::string_view new_value) override;

    using XmlCharacterData::Data;
    void Data(std::string_view new_data) override;

    void WriteTo(XmlWriter &xml_writer) const override;
protected:

    XmlNodeType _getNodeType() const override;
};

}