#pragma once

#include <cppdotnet/System/IO/StringWriter.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/XmlImplementation.hpp>
#include <cppdotnet/System/Xml/XmlDocument.hpp>

struct XmlNodeTestFixture
{
    XmlNodeTestFixture()
        :
        string_writer( std::make_shared<System::IO::StringWriter>() ),
        xml_writer( System::Xml::XmlWriter::Create( string_writer ) ),
        xml_implementation( std::make_shared<System::Xml::XmlImplementation>() ),
        xml_doc( xml_implementation->CreateDocument() )
    {
    }

    std::shared_ptr<System::IO::StringWriter> string_writer;
    std::unique_ptr<System::Xml::XmlWriter>   xml_writer;
    std::shared_ptr<System::Xml::XmlImplementation> xml_implementation;
    std::shared_ptr<System::Xml::XmlDocument>       xml_doc;
};