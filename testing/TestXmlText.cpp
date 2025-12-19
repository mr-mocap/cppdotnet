#include <cppdotnet/System/Xml/XmlText.hpp>
#include <cppdotnet/System/Xml/XmlNodeList.hpp>
#include "UnitTesting.hpp"
#include "XmlNodeTestFixture.hpp"
#include <cstdlib>
#include <cassert>


namespace TestXmlText
{

void DefaultConstructedXmlText()
{
    System::Xml::XmlText text_node;

    assert( text_node.LocalName() == "#text" );
    assert( text_node.Name() == "#text" );
    assert( text_node.OwnerDocument() == nullptr );
    assert( text_node.NodeType() == System::Xml::XmlNodeType::Text );

    assert( text_node.Value().empty() );

    assert( !text_node.HasChildNodes() );
    assert( text_node.ChildNodes().Count() == 0 );

    assert( text_node.Attributes().Count() == 0 );
}

void ConstructedWithDataOnly()
{
    const char *test_string_data = "This is some text";
    System::Xml::XmlText text_node( test_string_data, nullptr );

    assert( text_node.LocalName() == "#text" );
    assert( text_node.Name() == "#text" );
    assert( text_node.OwnerDocument() == nullptr );
    assert( text_node.NodeType() == System::Xml::XmlNodeType::Text );

    assert( text_node.Value() == test_string_data );

    assert( !text_node.HasChildNodes() );
    assert( text_node.ChildNodes().Count() == 0 );

    assert( text_node.Attributes().Count() == 0 );
}

void Run()
{
    DefaultConstructedXmlText();
    ConstructedWithDataOnly();
}

}

int main(void)
{
    TestXmlText::Run();
    return EXIT_SUCCESS;
}