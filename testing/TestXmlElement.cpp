#include <cppdotnet/System/Xml/XmlElement.hpp>
#include <cppdotnet/System/Xml/XmlText.hpp>
#include <cppdotnet/System/Xml/XmlComment.hpp>
#include <cppdotnet/System/Xml/XmlDeclaration.hpp>
#include <cppdotnet/System/Xml/XmlDocumentType.hpp>
#include <cppdotnet/System/Xml/XmlProcessingInstruction.hpp>
#include <cppdotnet/System/Xml/XmlWhitespace.hpp>
#include <cppdotnet/System/Xml/XmlNodeList.hpp>
#include <cppdotnet/System/Xml/XmlAttribute.hpp>
#include <cstdlib>
#include "UnitTesting.hpp"
#include "XmlNodeTestFixture.hpp"


namespace TestXmlElement
{

void EmptyXmlElement()
{
    System::Xml::XmlElement element("", "book", "", nullptr);

    assert( element.LocalName() == "book" );
    assert( element.Name() == "book" );
    assert( element.OwnerDocument() == nullptr );
    assert( element.NodeType() == System::Xml::XmlNodeType::Element );

    assert( element.Value().empty() );

    assert( !element.HasChildNodes() );
    assert( element.ChildNodes().Count() == 0 );

    assert( element.Attributes().Count() == 0 );
}

void CannotAddXmlAttributeAsChildNodeToXmlElement()
{
    System::Xml::XmlElement element("", "book", "", nullptr);
    std::shared_ptr<System::Xml::XmlAttribute> attribute = std::make_shared<System::Xml::XmlAttribute>("", "attribute", "", nullptr);

    assert( element.LocalName() == "book" );
    assert( element.Name() == "book" );
    assert( element.OwnerDocument() == nullptr );
    assert( element.NodeType() == System::Xml::XmlNodeType::Element );

    assert( element.Value().empty() );

    assert( !element.HasChildNodes() );
    assert( element.ChildNodes().Count() == 0 );
    assert( element.Attributes().Count() == 0 );
    
    ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, element.AppendChild( attribute ) );
}

void CanOnlyCallSetAttributeWhenXmlElementHasDocument()
{
    // No XmlDocument
    {
        System::Xml::XmlElement element("", "book", "", nullptr);

        assert( element.LocalName() == "book" );
        assert( element.Name() == "book" );
        assert( element.OwnerDocument() == nullptr );
        assert( element.NodeType() == System::Xml::XmlNodeType::Element );

        assert( element.Value().empty() );

        assert( element.Attributes().Count() == 0 );
        assert( !element.HasChildNodes() );
        assert( element.ChildNodes().Count() == 0 );
        
        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, element.SetAttribute("attribute", "value") );
    }

    // With XmlDocument
    {
        XmlNodeTestFixture fixture;
        std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

        assert( element->LocalName() == "book" );
        assert( element->Name() == "book" );
        assert( element->OwnerDocument() == fixture.xml_doc );
        assert( element->NodeType() == System::Xml::XmlNodeType::Element );

        assert( element->Value().empty() );

        element->SetAttribute("attribute", "value");
    }
}

void AddingAttributeToXmlElementDoesNotAddToChildNodes()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    assert( element->LocalName() == "book" );
    assert( element->Name() == "book" );
    assert( element->OwnerDocument() == fixture.xml_doc );
    assert( element->NodeType() == System::Xml::XmlNodeType::Element );

    assert( element->Value().empty() );

    assert( element->Attributes().Count() == 0 );
    assert( !element->HasChildNodes() );
    assert( element->ChildNodes().Count() == 0 );
    
    element->SetAttribute("attribute", "value");

    assert( !element->HasChildNodes() );
    assert( element->ChildNodes().Count() == 0 );
}

void AddingAttributeToXmlElementAffectsAttributesCount()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    assert( element->LocalName() == "book" );
    assert( element->Name() == "book" );
    assert( element->OwnerDocument() == fixture.xml_doc );
    assert( element->NodeType() == System::Xml::XmlNodeType::Element );

    assert( element->Value().empty() );

    assert( element->Attributes().Count() == 0 );
    
    element->SetAttribute("attribute", "value");

    assert( element->Attributes().Count() == 1 );
}

void AddingAttributeToXmlElementAddsXmlAttributeNodeWithXmlTextChildToAttributes()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    assert( element->Attributes().Count() == 0 );

    element->SetAttribute( "color", "red" );

    assert( element->Attributes().Count() == 1 );
    assert( element->Attributes().Item( 0 )->NodeType() == System::Xml::XmlNodeType::Attribute );

    std::shared_ptr<System::Xml::XmlNode> attribute = element->Attributes().Item( 0 );

    assert( attribute->HasChildNodes() );
    assert( attribute->ChildNodes().Item( 0 )->NodeType() == System::Xml::XmlNodeType::Text );
    assert( attribute->ChildNodes().Item( 0 )->Value() == "red" );
}

void CanAddAttributeWithNoValueToXmlElement()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    assert( element->LocalName() == "book" );
    assert( element->Name() == "book" );
    assert( element->OwnerDocument() == fixture.xml_doc );
    assert( element->NodeType() == System::Xml::XmlNodeType::Element );

    assert( element->Value().empty() );

    assert( element->Attributes().Count() == 0 );

    element->SetAttribute("attribute", "");

    assert( element->Attributes().Count() == 1 );
}

void GetAttributeReturnsEmptyWhenAddedAttributeHasNoValue()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    assert( element->LocalName() == "book" );
    assert( element->Name() == "book" );
    assert( element->OwnerDocument() == fixture.xml_doc );
    assert( element->NodeType() == System::Xml::XmlNodeType::Element );

    assert( element->Value().empty() );

    assert( element->Attributes().Count() == 0 );

    element->SetAttribute("attribute", "");

    assert( element->Attributes().Count() == 1 );
    assert( element->GetAttribute("attribute") == "" );
}

void GetAttributeReturnsEmptyWhenThereIsNoMatchingAttribute()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    assert( element->LocalName() == "book" );
    assert( element->Name() == "book" );
    assert( element->OwnerDocument() == fixture.xml_doc );
    assert( element->NodeType() == System::Xml::XmlNodeType::Element );

    assert( element->Value().empty() );

    assert( element->Attributes().Count() == 0 );

    element->SetAttribute("attribute", "");

    assert( element->Attributes().Count() == 1 );
    assert( element->GetAttribute("attribute_that_doesnt_exist") == "" );
}

void GetAttributeReturnsAttributeValueWhenSetAttributeHasValue()
{
    XmlNodeTestFixture fixture;
    std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");

    assert( element->LocalName() == "book" );
    assert( element->Name() == "book" );
    assert( element->OwnerDocument() == fixture.xml_doc );
    assert( element->NodeType() == System::Xml::XmlNodeType::Element );

    assert( element->Value().empty() );

    assert( element->Attributes().Count() == 0 );

    element->SetAttribute("attribute", "some value");

    assert( element->Attributes().Count() == 1 );
    assert( element->GetAttribute("attribute") == "some value" );
}

void OnlyCertainNodesCanBeChildrenOfXmlElement()
{
    // Create all the node types via XmlDocument...

    // XmlTextNode can be a child
    {
        XmlNodeTestFixture fixture;
        std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");
        std::shared_ptr<System::Xml::XmlText> text_node = fixture.xml_doc->CreateTextNode("text_node");

        assert( !element->HasChildNodes() );

        ASSERT_DOES_NOT_THROW_EXCEPTION( element->AppendChild( text_node ) );

        assert( element->HasChildNodes() );
        assert( element->ChildNodes().Count() == 1 );
    }

    // XmlComment can be a child
    {
        XmlNodeTestFixture fixture;
        std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");
        std::shared_ptr<System::Xml::XmlComment> comment_node = fixture.xml_doc->CreateComment("This is a comment");

        assert( !element->HasChildNodes() );

        ASSERT_DOES_NOT_THROW_EXCEPTION( element->AppendChild( comment_node ) );

        assert( element->HasChildNodes() );
        assert( element->ChildNodes().Count() == 1 );
    }

    // XmlElement can be a child
    {
        XmlNodeTestFixture fixture;
        std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");
        std::shared_ptr<System::Xml::XmlElement> element_node = fixture.xml_doc->CreateElement("title");

        assert( !element->HasChildNodes() );

        ASSERT_DOES_NOT_THROW_EXCEPTION( element->AppendChild( element_node ) );

        assert( element->HasChildNodes() );
        assert( element->ChildNodes().Count() == 1 );
    }

    // XmlProcessingInstruction can be a child
    {
        XmlNodeTestFixture fixture;
        std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");
        std::shared_ptr<System::Xml::XmlProcessingInstruction> pi_node = fixture.xml_doc->CreateProcessingInstruction("pi", "data");

        assert( !element->HasChildNodes() );

        ASSERT_DOES_NOT_THROW_EXCEPTION( element->AppendChild( pi_node ) );

        assert( element->HasChildNodes() );
        assert( element->ChildNodes().Count() == 1 );
    }

    // XmlWhitespace can be a child
    {
        XmlNodeTestFixture fixture;
        std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");
        std::shared_ptr<System::Xml::XmlWhitespace> ws_node = fixture.xml_doc->CreateWhitespace("   ");

        assert( !element->HasChildNodes() );

        ASSERT_DOES_NOT_THROW_EXCEPTION( element->AppendChild( ws_node ) );

        assert( element->HasChildNodes() );
        assert( element->ChildNodes().Count() == 1 );
    }

    // Now for the ones that CANNOT be
    
    // XmlAttribute
    {
        XmlNodeTestFixture fixture;
        std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");
        std::shared_ptr<System::Xml::XmlAttribute> attr_node = fixture.xml_doc->CreateAttribute("attr");

        assert( !element->HasChildNodes() );

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, element->AppendChild( attr_node ) );

        assert( !element->HasChildNodes() );
        assert( element->ChildNodes().Count() == 0 );
    }
    
    // XmlDeclaration
    {
        XmlNodeTestFixture fixture;
        std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");
        std::shared_ptr<System::Xml::XmlDeclaration> decl_node = fixture.xml_doc->CreateXmlDeclaration("1.0");

        assert( !element->HasChildNodes() );

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, element->AppendChild( decl_node ) );

        assert( !element->HasChildNodes() );
        assert( element->ChildNodes().Count() == 0 );
    }

    // XmlDocumentType
    {
        XmlNodeTestFixture fixture;
        std::shared_ptr<System::Xml::XmlElement> element = fixture.xml_doc->CreateElement("book");
        std::shared_ptr<System::Xml::XmlDocumentType> dt_node = fixture.xml_doc->CreateDocumentType("doctype");

        assert( !element->HasChildNodes() );

        ASSERT_THROWS_EXCEPTION( System::InvalidOperationException, element->AppendChild( dt_node ) );

        assert( !element->HasChildNodes() );
        assert( element->ChildNodes().Count() == 0 );
    }
}

void Run()
{
    EmptyXmlElement();
    CannotAddXmlAttributeAsChildNodeToXmlElement();
    CanOnlyCallSetAttributeWhenXmlElementHasDocument();
    AddingAttributeToXmlElementDoesNotAddToChildNodes();
    AddingAttributeToXmlElementAffectsAttributesCount();
    CanAddAttributeWithNoValueToXmlElement();
    GetAttributeReturnsEmptyWhenAddedAttributeHasNoValue();
    GetAttributeReturnsEmptyWhenThereIsNoMatchingAttribute();
    GetAttributeReturnsAttributeValueWhenSetAttributeHasValue();
    OnlyCertainNodesCanBeChildrenOfXmlElement();
    AddingAttributeToXmlElementAddsXmlAttributeNodeWithXmlTextChildToAttributes();
}

}

int main() {
    TestXmlElement::Run();
    return EXIT_SUCCESS;
}