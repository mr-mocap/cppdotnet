#pragma once

#include <cppdotnet/System/Xml/XmlLinkedNode.hpp>

namespace System::Xml
{

class XmlProcessingInstruction : public XmlLinkedNode
{
public:
    XmlProcessingInstruction();
    XmlProcessingInstruction(std::string_view target, std::shared_ptr<XmlDocument> document);
    XmlProcessingInstruction(std::string_view target, std::string_view data, std::shared_ptr<XmlDocument> document);
    XmlProcessingInstruction(const XmlProcessingInstruction &other);
   ~XmlProcessingInstruction() override = default;

    XmlProcessingInstruction &operator =(const XmlProcessingInstruction &other);
    XmlProcessingInstruction &operator =(XmlProcessingInstruction &&other);

    std::shared_ptr<XmlNode> CloneNode(bool deep) const override;

    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;

    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

    std::string_view Target() const
    {
        return Name();
    }

    std::string_view Data() const
    {
        return _data;
    }

    void Data(std::string_view new_data)
    {
        _data = new_data;
    }

    void WriteTo(XmlWriter &xml_writer) const override;
protected:
    std::string _data;

    XmlNodeType _getNodeType() const override;
};

}