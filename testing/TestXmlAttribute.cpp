#include <cppdotnet/System/Xml/XmlAttribute.hpp>
#include <cppdotnet/System/Xml/XmlComment.hpp>
#include <cppdotnet/System/Xml/XmlDeclaration.hpp>
#include <cppdotnet/System/Xml/XmlElement.hpp>
#include <cppdotnet/System/Xml/XmlProcessingInstruction.hpp>
#include <cppdotnet/System/Xml/XmlWhitespace.hpp>
#include <cppdotnet/System/Xml/XmlText.hpp>
#include <cppdotnet/System/Xml/XmlComment.hpp>
#include <cppdotnet/System/Xml/XmlNodeList.hpp>
#include "XmlNodeTestFixture.hpp"
#include "UnitTesting.hpp"
#include <cstdlib>


namespace TestXmlAttribute
{

void ConstructedWithNameOnly()
{
    System::Xml::XmlAttribute attribute("", "name", "", nullptr);

    assert( attribute.Name() == "name" );
    assert( attribute.Value() == "" );
}

void CanAppendTextNodeChild()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
    
    assert( attribute->Name() == "color" );
    assert( attribute->Value() == "" );
    assert( attribute->OuterXml() == "color=\"\"" );

    std::shared_ptr<System::Xml::XmlText> text = fixture.xml_doc->CreateTextNode("red");

    assert( text->Name() == "#text" );
    assert( text->Value() == "red" );

    attribute->AppendChild( text );

    assert( attribute->Value() == "red" );
    assert( attribute->OuterXml() == "color=\"red\"" );
}

void CanOnlyAppendTextNodeChild()
{
    XmlNodeTestFixture fixture;

    // The XmlTextNode case...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlText> text = fixture.xml_doc->CreateTextNode("red");

        ASSERT_DOES_NOT_THROW_EXCEPTION( attribute->AppendChild( text ) );
    }

    // Another XmlAttribute...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlAttribute> child = fixture.xml_doc->CreateAttribute("red");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->AppendChild( child ) );
    }

    // XmlElement...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlElement> child = fixture.xml_doc->CreateElement("name");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->AppendChild( child ) );
    }

    // XmlComment...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlComment> child = fixture.xml_doc->CreateComment("This is a comment");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->AppendChild( child ) );
    }

    // XmlDeclaration...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlDeclaration> child = fixture.xml_doc->CreateXmlDeclaration("1.1");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->AppendChild( child ) );
    }

    // XmlElement...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlElement> child = fixture.xml_doc->CreateElement("bool");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->AppendChild( child ) );
    }

    // XmlProcessingInstruction...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlProcessingInstruction> child = fixture.xml_doc->CreateProcessingInstruction("xml", "1.0");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->AppendChild( child ) );
    }

    // XmlWhitespace...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlWhitespace> child = fixture.xml_doc->CreateWhitespace("   ");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->AppendChild( child ) );
    }
}

void CanOnlyAppendASingleTextNodeChild()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
    std::shared_ptr<System::Xml::XmlText> text = fixture.xml_doc->CreateTextNode("red");

    ASSERT_DOES_NOT_THROW_EXCEPTION( attribute->AppendChild( text ) );

    assert( attribute->HasChildNodes() );
    assert( attribute->ChildNodes().Count() == 1 );

    std::shared_ptr<System::Xml::XmlText> text2 = fixture.xml_doc->CreateTextNode("blue");

    ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->AppendChild( text2 ) );
}

void CanPrependTextNodeChild()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
    
    assert( attribute->Name() == "color" );
    assert( attribute->Value() == "" );
    assert( attribute->OuterXml() == "color=\"\"" );

    std::shared_ptr<System::Xml::XmlText> text = fixture.xml_doc->CreateTextNode("red");

    assert( text->Name() == "#text" );
    assert( text->Value() == "red" );

    attribute->PrependChild( text );

    assert( attribute->Value() == "red" );
    assert( attribute->OuterXml() == "color=\"red\"" );
}

void CanOnlyPrependTextNodeChild()
{
    XmlNodeTestFixture fixture;

    // The XmlTextNode case...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlText> text = fixture.xml_doc->CreateTextNode("red");

        ASSERT_DOES_NOT_THROW_EXCEPTION( attribute->PrependChild( text ) );
    }

    // Another XmlAttribute...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlAttribute> child = fixture.xml_doc->CreateAttribute("red");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->PrependChild( child ) );
    }

    // XmlElement...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlElement> child = fixture.xml_doc->CreateElement("name");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->PrependChild( child ) );
    }

    // XmlComment...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlComment> child = fixture.xml_doc->CreateComment("This is a comment");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->PrependChild( child ) );
    }

    // XmlDeclaration...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlDeclaration> child = fixture.xml_doc->CreateXmlDeclaration("1.1");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->PrependChild( child ) );
    }

    // XmlElement...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlElement> child = fixture.xml_doc->CreateElement("bool");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->PrependChild( child ) );
    }

    // XmlProcessingInstruction...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlProcessingInstruction> child = fixture.xml_doc->CreateProcessingInstruction("xml", "1.0");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->PrependChild( child ) );
    }

    // XmlWhitespace...
    {
        std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
        std::shared_ptr<System::Xml::XmlWhitespace> child = fixture.xml_doc->CreateWhitespace("   ");

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->PrependChild( child ) );
    }
}

void CanOnlyPrependASingleTextNodeChild()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlAttribute> attribute = fixture.xml_doc->CreateAttribute("color");
    std::shared_ptr<System::Xml::XmlText> text = fixture.xml_doc->CreateTextNode("red");

    ASSERT_DOES_NOT_THROW_EXCEPTION( attribute->AppendChild( text ) );

    assert( attribute->HasChildNodes() );
    assert( attribute->ChildNodes().Count() == 1 );

    std::shared_ptr<System::Xml::XmlText> text2 = fixture.xml_doc->CreateTextNode("blue");

    ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, attribute->PrependChild( text2 ) );
}

void Run()
{
    ConstructedWithNameOnly();
    CanAppendTextNodeChild();
    CanOnlyAppendTextNodeChild();
    CanOnlyAppendASingleTextNodeChild();

    CanPrependTextNodeChild();
    CanOnlyPrependTextNodeChild();
    CanOnlyPrependASingleTextNodeChild();
}

}

int main()
{
    TestXmlAttribute::Run();
    return EXIT_SUCCESS;
}