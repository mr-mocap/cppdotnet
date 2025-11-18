#pragma once

#include <cppdotnet/System/Xml/XmlNameTable.hpp>

namespace System::Xml
{

class XmlDocument;

class XmlImplementation
{
public:
    XmlImplementation();
    XmlImplementation(std::shared_ptr<XmlNameTable> name_table);

    virtual std::shared_ptr<XmlDocument> CreateDocument();

    std::shared_ptr<XmlNameTable> NameTable() const;
protected:
    std::shared_ptr<XmlNameTable> _name_table;
};

}