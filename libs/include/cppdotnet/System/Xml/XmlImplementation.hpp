#pragma once

#include <cppdotnet/System/Xml/XmlNameTable.hpp>

namespace System::Xml
{

class XmlDocument;

class XmlImplementation
{
public:
    XmlImplementation();
    XmlImplementation(std::unique_ptr<XmlNameTable> &&name_table);
    XmlImplementation(std::shared_ptr<const XmlNameTable> name_table);
    XmlImplementation(std::shared_ptr<XmlNameTable> name_table);
    virtual ~XmlImplementation();

    virtual std::shared_ptr<XmlDocument> CreateDocument();

    std::shared_ptr<const XmlNameTable> NameTable() const;
    std::shared_ptr<XmlNameTable>       NameTable();
protected:
    std::shared_ptr<XmlNameTable> _name_table;
};

}