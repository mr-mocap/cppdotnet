#include <cstdlib>
#include <cassert>
#include <cppdotnet/System/IO/StringWriter.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/XmlImplementation.hpp>
#include <cppdotnet/System/Xml/XmlComment.hpp>
#include <cppdotnet/System/Xml/XmlDeclaration.hpp>
#include <cppdotnet/System/Xml/XmlElement.hpp>
#include <cppdotnet/System/Xml/XmlProcessingInstruction.hpp>
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

void XmlProcessingInstructionWithTarget()
{
    XmlNodeTestFixture fixture;

    std::shared_ptr<System::Xml::XmlProcessingInstruction> pi = fixture.xml_doc->CreateProcessingInstruction("xml-stylesheet");

    assert( pi->Target() == "xml-stylesheet" );
    assert( pi->Data().empty() );

    pi->WriteTo( *(fixture.xml_writer) );

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    assert( data_written == "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-stylesheet?>" );
}

void XmlProcessingInstructionWithTargetAndData()
{
    XmlNodeTestFixture fixture;

    const char *target = "xml-stylesheet";
    const char *data = "type=\"text/xsl\" href=\"style.xsl\"";
    std::shared_ptr<System::Xml::XmlProcessingInstruction> pi = fixture.xml_doc->CreateProcessingInstruction(target, data);

    assert( pi->Target() == target );
    assert( pi->Data() == data );

    pi->WriteTo( *(fixture.xml_writer) );

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    std::string expected = std::format("<?xml version=\"1.0\" encoding=\"UTF-8\"?><?{} {}?>", target, data);

    assert( data_written == expected );
}

void XmlProcessingInstructionWrittenTwice()
{
    XmlNodeTestFixture fixture;

    const char *target = "xml-stylesheet";
    const char *data = "type=\"text/xsl\" href=\"style.xsl\"";
    std::shared_ptr<System::Xml::XmlProcessingInstruction> pi = fixture.xml_doc->CreateProcessingInstruction(target, data);

    assert( pi->Target() == target );
    assert( pi->Data() == data );

    pi->WriteTo( *(fixture.xml_writer) );

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    std::string expected = std::format("<?xml version=\"1.0\" encoding=\"UTF-8\"?><?{} {}?>", target, data);

    assert( data_written == expected );

    pi->WriteTo( *(fixture.xml_writer) );

    std::string new_data_written = fixture.string_writer->GetStringBuilder().ToString();
    std::string new_expected = expected + std::format("<?{} {}?>", target, data);

    assert( new_data_written == new_expected );
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

void XmlCommentEmptyIsWrittenCorrectly()
{
    XmlNodeTestFixture fixture;

    std::shared_ptr<System::Xml::XmlComment> comment = fixture.xml_doc->CreateComment("");

    assert( comment->Name() == "#comment" );
    assert( comment->Value().HasValue() );
    assert( comment->Value().Value() == "" );
    assert( fixture.xml_writer->WriteState() == System::Xml::WriteState::Start );

    comment->WriteTo( *(fixture.xml_writer) );

    assert( fixture.xml_writer->WriteState() == System::Xml::WriteState::Prolog );

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    assert( data_written == "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!---->" );
}

void XmlCommentWithDataIsWrittenCorrectly()
{
    XmlNodeTestFixture fixture;

    std::shared_ptr<System::Xml::XmlComment> comment = fixture.xml_doc->CreateComment("This should be a comment");

    assert( comment->Name() == "#comment" );
    assert( comment->Value().HasValue() );
    assert( comment->Value().Value() == "This should be a comment" );
    assert( fixture.xml_writer->WriteState() == System::Xml::WriteState::Start );

    comment->WriteTo( *(fixture.xml_writer) );

    assert( fixture.xml_writer->WriteState() == System::Xml::WriteState::Prolog );

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    assert( data_written == "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!--This should be a comment-->" );
}

void Run()
{
    EmptyXmlDeclaration();
    XmlDeclarationWithEncoding();
    XmlProcessingInstructionWithTarget();
    XmlProcessingInstructionWithTargetAndData();
    XmlProcessingInstructionWrittenTwice();
    EmptyXmlElement();
    CannotAddValueToXmlElement();
    XmlElementWithTextNodeChild();
    XmlCommentEmptyIsWrittenCorrectly();
    XmlCommentWithDataIsWrittenCorrectly();
}

}

int main(void)
{
    TestXmlNodeWriteTo::Run();
    return EXIT_SUCCESS;
}