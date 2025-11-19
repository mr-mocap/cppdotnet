#pragma once

#include <cppdotnet/System/Xml/XmlNodeList.hpp>
#include <cppdotnet/System/Collections/Generic/List.hpp>

namespace System::Xml::Private
{

class DefaultNodeListImplementation : public Xml::XmlNodeList
{
public:
    DefaultNodeListImplementation() = default;
    DefaultNodeListImplementation(const DefaultNodeListImplementation &other);
   ~DefaultNodeListImplementation() override;

    DefaultNodeListImplementation &operator =(const DefaultNodeListImplementation &other);

    int Count() const override;

    std::shared_ptr<XmlNode> operator [](size_t index) const override;
    std::shared_ptr<XmlNode> operator [](int    index) const override;

    std::shared_ptr<XmlNode> Item(size_t index) const override;
    std::shared_ptr<XmlNode> Item(int    index) const override;

    std::shared_ptr<XmlNodeList> MemberwiseClone() const override;

    std::shared_ptr<XmlNode> Append(std::shared_ptr<XmlNode> new_node) override;

    std::shared_ptr<XmlNode> Insert(size_t index, std::shared_ptr<XmlNode> new_node) override;
    std::shared_ptr<XmlNode> Insert(int    index, std::shared_ptr<XmlNode> new_node) override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> child_node);
    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child);
protected:
    System::Collections::Generic::List<std::shared_ptr<XmlNode>> _nodes;
};

}