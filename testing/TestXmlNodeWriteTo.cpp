#include <cstdlib>
#include <cassert>
#include <cppdotnet/System/IO/StringWriter.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/XmlImplementation.hpp>
#include <cppdotnet/System/Xml/XmlElement.hpp>
#include <cppdotnet/System/Xml/XmlDocument.hpp>

namespace TestXmlNodeWriteTo
{

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

void EmptyXmlElement()
{
    XmlNodeTestFixture fixture;

    fixture.xml_writer->WriteStartDocument();

    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    assert( element->Name() == "book" );

    std::string prolog_written = fixture.string_writer->GetStringBuilder().ToString();

    element->WriteTo( *(fixture.xml_writer) );

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    if (data_written.starts_with( prolog_written ) )
        data_written.erase( data_written.begin(), std::next( data_written.begin(), prolog_written.size() ) );

    assert( data_written == "<book />" );
}

void XmlElementWithValue()
{
    XmlNodeTestFixture fixture;

    fixture.xml_writer->WriteStartDocument();

    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    element->Value( std::string("Pride And Prejudice") );

    assert( element->Name() == "book" );
    assert( !element->Value().HasValue() );

    std::string prolog_written = fixture.string_writer->GetStringBuilder().ToString();

    element->WriteTo( *(fixture.xml_writer) );

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    if (data_written.starts_with( prolog_written ) )
        data_written.erase( data_written.begin(), std::next( data_written.begin(), prolog_written.size() ) );

    assert( data_written == "<book>Pride And Prejudice</book>" );
}

void Run()
{
    EmptyXmlElement();
    XmlElementWithValue();
}

}

int main(void)
{
    TestXmlNodeWriteTo::Run();
    return EXIT_SUCCESS;
}