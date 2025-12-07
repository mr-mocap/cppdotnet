#pragma once

#include <cppdotnet/System/Xml/XmlLinkedNode.hpp>

namespace System::Xml
{

class XmlCharacterData : public XmlLinkedNode
{
public:
    XmlCharacterData();
    XmlCharacterData(std::shared_ptr<XmlDocument> doc, std::string_view name);
    XmlCharacterData(std::string_view data, std::shared_ptr<XmlDocument> doc, std::string_view name);
    XmlCharacterData(const XmlCharacterData &other);
    XmlCharacterData(XmlCharacterData &&other);
   ~XmlCharacterData() override = default;

    XmlCharacterData &operator =(const XmlCharacterData &other);
    XmlCharacterData &operator =(XmlCharacterData &&other);

    virtual void AppendData(std::string_view data);

    Nullable<std::string> Value() const override;

    virtual Nullable<std::string> Data() const;
            void                  Data(std::nullopt_t null_value)
            {
                Data( Nullable<std::string_view>{ null_value } );
            }
            void                  Data(std::string_view new_data)
            {
                Data( Nullable<std::string_view>{ new_data } );
            }
            void                  Data(const char *new_data)
            {
                Data( std::string_view( new_data ) );
            }

    virtual std::size_t Length() const;

    void RemoveAll() override;

    std::shared_ptr<XmlNode> RemoveChild(std::shared_ptr<XmlNode> old_child) override;

    std::shared_ptr<XmlNode> ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child) override;

protected:
    Nullable<std::string> _value;

    void Value(Nullable<std::string> new_value) override;

    virtual void Data(Nullable<std::string_view> new_data);
};

}