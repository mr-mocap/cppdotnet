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
    XmlImplementation(std::shared_ptr<XmlNameTable> name_table);
    virtual ~XmlImplementation();

    virtual std::shared_ptr<XmlDocument> CreateDocument() const;

    std::shared_ptr<XmlNameTable> NameTable() const;
protected:
    std::shared_ptr<XmlNameTable> _name_table;
};

}