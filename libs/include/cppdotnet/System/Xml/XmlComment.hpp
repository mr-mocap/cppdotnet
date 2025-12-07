#pragma once

#include <cppdotnet/System/Xml/XmlCharacterData.hpp>

namespace System::Xml
{

class XmlComment : public XmlCharacterData
{
public:
    XmlComment() = default;
    XmlComment(std::shared_ptr<XmlDocument> doc);
    XmlComment(std::string_view comment, std::shared_ptr<XmlDocument> doc);
    XmlComment(const XmlComment &other);
    XmlComment(XmlComment &&other);
   ~XmlComment() override = default;

    XmlComment &operator =(const XmlComment &other);
    XmlComment &operator =(XmlComment &&other);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    void WriteTo(XmlWriter &xml_writer) const override;
protected:

    XmlNodeType _getNodeType() const override;
};

}