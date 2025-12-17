#pragma once

#include <cppdotnet/System/Xml/XmlCharacterData.hpp>

namespace System::Xml
{

class XmlText : public XmlCharacterData
{
public:
    XmlText();
    XmlText(std::shared_ptr<XmlDocument> doc);
    XmlText(std::string_view data, std::shared_ptr<XmlDocument> doc);
    XmlText(const XmlText &other);
    XmlText(XmlText &&other);
   ~XmlText() override = default;

    XmlText &operator =(const XmlText &other);
    XmlText &operator =(XmlText &&other);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    void WriteTo(XmlWriter &xml_writer) const override;
protected:

    XmlNodeType _getNodeType() const override;
};

}