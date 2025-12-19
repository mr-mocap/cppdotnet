#pragma once

#include <cppdotnet/System/Xml/XmlLinkedNode.hpp>

namespace System::Xml
{

class XmlCharacterData : public XmlLinkedNode
{
public:
    XmlCharacterData() = default;
    XmlCharacterData(std::shared_ptr<XmlDocument> doc, std::string_view name);
    XmlCharacterData(std::string_view data, std::shared_ptr<XmlDocument> doc, std::string_view name);
    XmlCharacterData(const XmlCharacterData &other);
    XmlCharacterData(XmlCharacterData &&other);
   ~XmlCharacterData() override = default;

    XmlCharacterData &operator =(const XmlCharacterData &other);
    XmlCharacterData &operator =(XmlCharacterData &&other);

    virtual void AppendData(std::string_view data);

    using XmlLinkedNode::Value;
    std::string_view Value() const override;
    void             Value(std::string_view new_value) override;

    virtual std::string_view Data() const;
    virtual void             Data(std::string_view new_data);
            void             Data(const char *new_data)
            {
                if ( new_data )
                    Data( std::string_view( new_data ) );
                else
                    Data( std::string_view() );
            }

    virtual std::size_t Length() const;

    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;

    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

protected:
    std::string _value;

    XmlCharacterData(std::shared_ptr<XmlNodeList>   specific_children_object,
                     NodeConstructionParameters   &&parameters);
};

}