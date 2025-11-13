#pragma once

#include <cppdotnet/System/Xml/XmlNode.hpp>
#include <cppdotnet/System/Xml/XmlNameTable.hpp>
#include <cppdotnet/System/Private/private.hpp>
#include <memory>

namespace System::Xml
{

class XmlDocument : public XmlNode
{
public:
    XmlDocument();
    XmlDocument(const XmlNameTable &name_table)
        :
        _name_table( name_table.MemberwiseClone() )
    {
    }
    XmlDocument(std::unique_ptr<XmlNameTable> &&name_table)
        :
        _name_table( std::move(name_table) )
    {
        INVARIANT( _name_table );
    }
    XmlDocument(std::shared_ptr<XmlNameTable> &name_table)
        :
        _name_table( name_table )
    {
        INVARIANT( _name_table );
    }
    XmlDocument(std::shared_ptr<XmlNameTable> &&name_table)
        :
        _name_table( std::move(name_table) )
    {
        INVARIANT( _name_table );
    }
   ~XmlDocument() override = default;
    
    const XmlNameTable &NameTable() const
    {
        INVARIANT( _name_table );

        return *_name_table;
    }

          XmlNameTable &NameTable()
    {
        INVARIANT( _name_table );

        return *_name_table;
    }

    std::string_view Name() const override;
protected:
    std::shared_ptr<XmlNameTable> _name_table;

    XmlNodeType _getNodeType() override const;
};

}