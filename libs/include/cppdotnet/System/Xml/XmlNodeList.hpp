#pragma once

#include <cppdotnet/System/Xml/XmlNode.hpp>

namespace System::Xml
{

class XmlNodeList
{
public:
    virtual ~XmlNodeList() { };

    virtual int Count() const = 0;

    virtual std::shared_ptr<XmlNode> operator [](size_t index) const = 0;
    virtual std::shared_ptr<XmlNode> operator [](int index) const = 0;

    virtual std::shared_ptr<XmlNode> Item(size_t index) const = 0;
    virtual std::shared_ptr<XmlNode> Item(int index) const = 0;

    virtual std::shared_ptr<XmlNodeList> MemberwiseClone() const = 0;

    virtual std::shared_ptr<XmlNode> Append(std::shared_ptr<XmlNode> new_node) = 0;

    virtual std::shared_ptr<XmlNode> Insert(size_t index, std::shared_ptr<XmlNode> new_node) = 0;
    virtual std::shared_ptr<XmlNode> Insert(int    index, std::shared_ptr<XmlNode> new_node) = 0;
};

}