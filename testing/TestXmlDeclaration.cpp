#include <cstdlib>
#include <cassert>
#include <cppdotnet/System/Xml/XmlDeclaration.hpp>
#include "XmlNodeTestFixture.hpp"

namespace TestXmlDeclaration
{

void EmptyXmlDeclaration()
{
    System::Xml::XmlDeclaration declaration;

    assert( declaration.LocalName() == "xml" );
    assert( declaration.Name() == "xml" );
    assert( declaration.Version() == "1.0" );
    assert( declaration.Encoding().empty() );
    assert( declaration.Standalone().empty() );
    assert( declaration.OwnerDocument() == nullptr );
    assert( declaration.NodeType() == System::Xml::XmlNodeType::XmlDeclaration );

    assert( declaration.Value().HasValue() );
    assert( declaration.Value().Value() == "version=\"1.0\"" );
}

void XmlDeclarationWithVersion()
{
    System::Xml::XmlDeclaration declaration("1.1", nullptr);

    assert( declaration.LocalName() == "xml" );
    assert( declaration.Name() == "xml" );
    assert( declaration.Version() == "1.1" );
    assert( declaration.Encoding().empty() );
    assert( declaration.Standalone().empty() );
    assert( declaration.OwnerDocument() == nullptr );
    assert( declaration.NodeType() == System::Xml::XmlNodeType::XmlDeclaration );

    assert( declaration.Value().HasValue() );
    assert( declaration.Value().Value() == "version=\"1.1\"" );
}

void XmlDeclarationWithVersionAndOwnerDocument()
{
    XmlNodeTestFixture fixture;
    System::Xml::XmlDeclaration declaration("1.1", fixture.xml_doc);

    assert( declaration.LocalName() == "xml" );
    assert( declaration.Name() == "xml" );
    assert( declaration.Version() == "1.1" );
    assert( declaration.Encoding().empty() );
    assert( declaration.Standalone().empty() );
    assert( declaration.OwnerDocument() == fixture.xml_doc );
    assert( declaration.NodeType() == System::Xml::XmlNodeType::XmlDeclaration );

    assert( declaration.Value().HasValue() );
    assert( declaration.Value().Value() == "version=\"1.1\"" );
}

void XmlDeclarationWithVersionAndEncoding()
{
    System::Xml::XmlDeclaration declaration("1.1", "UTF-8", nullptr);

    assert( declaration.LocalName() == "xml" );
    assert( declaration.Name() == "xml" );
    assert( declaration.Version() == "1.1" );
    assert( declaration.Encoding() == "UTF-8" );
    assert( declaration.Standalone().empty() );
    assert( declaration.OwnerDocument() == nullptr );
    assert( declaration.NodeType() == System::Xml::XmlNodeType::XmlDeclaration );

    assert( declaration.Value().HasValue() );
    assert( declaration.Value().Value() == "version=\"1.1\" encoding=\"UTF-8\"" );
}

void XmlDeclarationWithVersionAndEncodingAndOwnerDocument()
{
    XmlNodeTestFixture fixture;
    System::Xml::XmlDeclaration declaration("1.1", "UTF-8", fixture.xml_doc);

    assert( declaration.LocalName() == "xml" );
    assert( declaration.Name() == "xml" );
    assert( declaration.Version() == "1.1" );
    assert( declaration.Encoding() == "UTF-8" );
    assert( declaration.Standalone().empty() );
    assert( declaration.OwnerDocument() == fixture.xml_doc );
    assert( declaration.NodeType() == System::Xml::XmlNodeType::XmlDeclaration );

    assert( declaration.Value().HasValue() );
    assert( declaration.Value().Value() == "version=\"1.1\" encoding=\"UTF-8\"" );
}

void Run()
{
    EmptyXmlDeclaration();
    XmlDeclarationWithVersion();
    XmlDeclarationWithVersionAndOwnerDocument();
    XmlDeclarationWithVersionAndEncoding();
}

}

int main(void)
{
    TestXmlDeclaration::Run();

    return EXIT_SUCCESS;
}