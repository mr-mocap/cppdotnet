#include <cstdlib>
#include <cassert>
#include <cppdotnet/System/IO/StringWriter.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/XmlImplementation.hpp>
#include <cppdotnet/System/Xml/XmlDeclaration.hpp>
#include <cppdotnet/System/Xml/XmlElement.hpp>
#include <cppdotnet/System/Xml/XmlText.hpp>
#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include "XmlNodeTestFixture.hpp"

namespace TestXmlNodeWriteTo
{

void EmptyXmlDeclaration()
{
    XmlNodeTestFixture fixture;

    std::shared_ptr<System::Xml::XmlDeclaration> declaration = fixture.xml_doc->CreateXmlDeclaration("1.0");

    assert( declaration->Name() == "xml" );

    declaration->WriteTo( *(fixture.xml_writer) );

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    assert( data_written == "<?xml version=\"1.0\"?>" );
}

void XmlDeclarationWithEncoding()
{
    XmlNodeTestFixture fixture;

    std::shared_ptr<System::Xml::XmlDeclaration> declaration = fixture.xml_doc->CreateXmlDeclaration("1.0", "UTF-8");

    assert( declaration->Name() == "xml" );

    declaration->WriteTo( *(fixture.xml_writer) );

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    assert( data_written == "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" );
}

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

void CannotAddValueToXmlElement()
{
    XmlNodeTestFixture fixture;

    fixture.xml_writer->WriteStartDocument();

    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    assert( element->Name() == "book" );
    assert( !element->Value().HasValue() );

    try
    {
        element->Value( "Pride And Prejudice" );
        assert( false );
    }
    catch (const System::InvalidOperationException &e)
    {
        assert( true);
    }
}

void XmlElementWithTextNodeChild()
{
    XmlNodeTestFixture fixture;

    fixture.xml_writer->WriteStartDocument();

    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    assert( element->Name() == "book" );
    assert( !element->Value().HasValue() );

    std::string prolog_written = fixture.string_writer->GetStringBuilder().ToString();

    {
        std::shared_ptr<System::Xml::XmlNode> text_node = fixture.xml_doc->CreateTextNode( "Pride And Prejudice" );

        element->AppendChild( text_node );
    }

    element->WriteTo( *(fixture.xml_writer) );

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    if (data_written.starts_with( prolog_written ) )
        data_written.erase( data_written.begin(), std::next( data_written.begin(), prolog_written.size() ) );

    assert( data_written == "<book>Pride And Prejudice</book>" );
}

void Run()
{
    EmptyXmlDeclaration();
    XmlDeclarationWithEncoding();
    EmptyXmlElement();
    CannotAddValueToXmlElement();
    XmlElementWithTextNodeChild();
}

}

int main(void)
{
    TestXmlNodeWriteTo::Run();
    return EXIT_SUCCESS;
}