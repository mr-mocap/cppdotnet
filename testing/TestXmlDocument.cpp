#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/XmlElement.hpp>
#include <cppdotnet/System/Xml/XmlWhitespace.hpp>
#include <cppdotnet/System/Xml/NameTable.hpp>
#include <cstdlib>
#include <cassert>
#include "UnitTesting.hpp"
#include "XmlNodeTestFixture.hpp"

namespace TestXmlDocument
{

void DefaultConstructed()
{
    System::Xml::XmlDocument d;

    assert( d.NameTable().empty() );
}

void ConstructWithReferenceToExternalNameTableCopiesTheExternalTable()
{
    System::Xml::NameTable nt;

    nt.Add( "Name" );

    assert( !nt.empty() );
    assert( nt.Get( "Name" ) == "Name" ); // "Name" is in there

    System::Xml::XmlDocument d( nt );

    // Test if they both contain the same data in the two NameTables
    assert( !d.NameTable().empty() );
    assert( d.NameTable().Get( "Name" ) == "Name" );

    // Add a new name into the external NameTable;
    nt.Add( "Test" );
    assert( nt.Get( "Test" ) == "Test" );

    // Demonstrate that the Document's NameTable is unaffected
    assert( d.NameTable().Get( "Test" ).empty() );
}

void ConstructWithSharedPointerToExternalNameTableRefersToTheExternalNameTable()
{
    std::shared_ptr<System::Xml::XmlNameTable> external_name_table = std::make_shared<System::Xml::NameTable>();

    assert( external_name_table->empty() );

    System::Xml::XmlDocument d( external_name_table );

    assert( d.NameTable().empty() );

    // Now, let's add something to the external table
    external_name_table->Add( "Test" );

    // Demonstrate that it was added...
    assert( external_name_table->Get( "Test" ) == "Test" );

    // Demonstrate that the Document's NameTable is also changed.
    assert( d.NameTable().Get( "Test" ) == "Test" );
}

void CreateWhitespaceWithEmptyString()
{
    XmlNodeTestFixture fixture;

    {
        std::shared_ptr<System::Xml::XmlWhitespace> node = fixture.xml_doc->CreateWhitespace("");
        std::string_view data = node->Data();

        assert( node->Name() == "#whitespace" );
        assert( data == "" );
    }
}

void CreateWhitespaceWithValidString()
{
    XmlNodeTestFixture fixture;

    {
        std::shared_ptr<System::Xml::XmlWhitespace> node = fixture.xml_doc->CreateWhitespace("    ");
        std::string_view data = node->Data();

        assert( node->Name() == "#whitespace" );
        assert( data == "    " );
    }
    {
        std::shared_ptr<System::Xml::XmlWhitespace> node = fixture.xml_doc->CreateWhitespace("\t");
        std::string_view data = node->Data();

        assert( node->Name() == "#whitespace" );
        assert( data == "\t" );
    }
    {
        std::shared_ptr<System::Xml::XmlWhitespace> node = fixture.xml_doc->CreateWhitespace("\r");
        std::string_view data = node->Data();

        assert( node->Name() == "#whitespace" );
        assert( data == "\r" );
    }
    {
        std::shared_ptr<System::Xml::XmlWhitespace> node = fixture.xml_doc->CreateWhitespace("\n");
        std::string_view data = node->Data();

        assert( node->Name() == "#whitespace" );
        assert( data == "\n" );
    }
    {
        std::shared_ptr<System::Xml::XmlWhitespace> node = fixture.xml_doc->CreateWhitespace(" \t\r\n");
        std::string_view data = node->Data();

        assert( node->Name() == "#whitespace" );
        assert( data == " \t\r\n" );
    }
}

void CreateWhitespaceWithInvalidString()
{
    XmlNodeTestFixture fixture;

    ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, fixture.xml_doc->CreateWhitespace("This is invalid data") );
    ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, fixture.xml_doc->CreateWhitespace("T") );
    ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, fixture.xml_doc->CreateWhitespace(" \t\r\nX") );
}

void EmptyDocumentOuterXml()
{
    XmlNodeTestFixture fixture;

    assert( fixture.xml_doc->OuterXml() == "" );
}

void DocumentWithOneEmptyElement()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlElement> node = fixture.xml_doc->CreateElement( "book" );

    assert( fixture.xml_doc->OuterXml() == "" );
    assert( node->OwnerDocument() == fixture.xml_doc );

    fixture.xml_doc->AppendChild( node );

    assert( fixture.xml_doc->OuterXml() == "<book />" );
    assert( node->OwnerDocument() == fixture.xml_doc );
}

void DocumentWithOneEmptyElement()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlElement> node = fixture.xml_doc->CreateElement( "book" );

    assert( fixture.xml_doc->OuterXml() == "" );
    assert( node->OwnerDocument() == fixture.xml_doc );

    fixture.xml_doc->AppendChild( node );

    assert( fixture.xml_doc->OuterXml() == "<book />" );
    assert( node->OwnerDocument() == fixture.xml_doc );
}

void Run()
{
    DefaultConstructed();
    ConstructWithReferenceToExternalNameTableCopiesTheExternalTable();
    ConstructWithSharedPointerToExternalNameTableRefersToTheExternalNameTable();
    CreateWhitespaceWithEmptyString();
    CreateWhitespaceWithValidString();
    CreateWhitespaceWithInvalidString();
    EmptyDocumentOuterXml();
    DocumentWithOneEmptyElement();
}

}

int main(void)
{
    TestXmlDocument::Run();
    return EXIT_SUCCESS;
}