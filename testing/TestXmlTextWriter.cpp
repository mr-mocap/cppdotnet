#include <cstdlib>
#include <cassert>
#include <cppdotnet/System/Xml/XmlTextWriter.hpp>
#include <cppdotnet/System/IO/StringWriter.hpp>
#include "UnitTesting.hpp"


struct XmlWriterTestFixture
{
    XmlWriterTestFixture()
        :
        string_writer{ std::make_shared<System::IO::StringWriter>() },
        xml_writer{ System::Xml::XmlWriter::Create( string_writer ) }
    {
    }

   ~XmlWriterTestFixture()
    {
        xml_writer.reset();
        string_writer.reset();
    }

    std::shared_ptr<System::IO::StringWriter> string_writer;
    std::unique_ptr<System::Xml::XmlWriter>   xml_writer;
};

namespace TestXmlTextWriter
{

void InitialXmlWriterState()
{
    XmlWriterTestFixture fixture;

    assert( fixture.string_writer->GetStringBuilder().Length() == 0 );
    assert( fixture.xml_writer->WriteState() == System::Xml::WriteState::Start );
    assert( fixture.xml_writer->Settings().OmitXmlDeclaration() == false );
}

void WriteStartDocumentProducesDefaultProlog()
{
    XmlWriterTestFixture fixture;

    assert( fixture.string_writer->GetStringBuilder().Length() == 0 );
    assert( fixture.xml_writer->WriteState() == System::Xml::WriteState::Start );
    assert( fixture.xml_writer->Settings().OmitXmlDeclaration() == false );

    fixture.xml_writer->WriteStartDocument();

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    assert( data_written == "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" );
}

void WriteStartDocumentProducesPrologWithOmittedDeclaration()
{
    XmlWriterTestFixture fixture;

    fixture.xml_writer->Settings().OmitXmlDeclaration( true );

    assert( fixture.string_writer->GetStringBuilder().Length() == 0 );
    assert( fixture.xml_writer->WriteState() == System::Xml::WriteState::Start );
    assert( fixture.xml_writer->Settings().OmitXmlDeclaration() == true );

    fixture.xml_writer->WriteStartDocument();

    std::string data_written = fixture.string_writer->GetStringBuilder().ToString();

    assert( data_written == "" );
}

void CallingWriteStartDocumentPutsWriteStateAtProlog()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

    xml_writer->WriteStartDocument();

    assert( xml_writer->WriteState() == System::Xml::WriteState::Prolog );
}

void CanOnlyCallWriteStartDocumentOnceAndWhileWriteStateIsStart()
{
    XmlWriterTestFixture fixture;

    assert( fixture.xml_writer->WriteState() == System::Xml::WriteState::Start );

    fixture.xml_writer->WriteStartDocument();

    assert( fixture.xml_writer->WriteState() == System::Xml::WriteState::Prolog );

    ASSERT_THROWS_EXCEPTION(System::SystemException, fixture.xml_writer->WriteStartDocument() );
}

void CanCallWriteProcessingInstructionInsteadOfWriteStartDocument()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

    std::string_view name = "xml-stylesheet";
    std::string_view value = "";

    xml_writer->WriteProcessingInstruction(name, value);

    assert( xml_writer->WriteState() == System::Xml::WriteState::Prolog );

    std::string_view output = string_writer->GetStringBuilder().ToString();

    assert( output == "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-stylesheet?>" );
}

void CallingWriteProcessingInstructionWithEmptyNameThrowsException()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

    ASSERT_THROWS_EXCEPTION(System::ArgumentException, xml_writer->WriteProcessingInstruction("", "Some Text") );
}

void CallingWriteStartDocumentProducesADefaultProlog()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

    xml_writer->WriteStartDocument();

    assert( string_writer->GetStringBuilder().ToString() == "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" );
}

void CallingWriteEndDocumentPutsXmlWriterBackInWriteStateOfStart()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

    xml_writer->WriteStartDocument();

    assert( xml_writer->WriteState() == System::Xml::WriteState::Prolog );

    xml_writer->WriteEndDocument();

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );
}

void SettingOmitXmlDeclarationToTrueAllowsWriteStartElementToBeImmediatelyCalled()
{
    {
        std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
        System::Xml::XmlWriterSettings settings;

        settings.OmitXmlDeclaration( true );

        assert( settings.OmitXmlDeclaration() );

        std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer, settings );

        assert( xml_writer->Settings().OmitXmlDeclaration() );
        assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

        xml_writer->WriteStartElement("book");

        assert( xml_writer->WriteState() == System::Xml::WriteState::Element );
        assert( string_writer->GetStringBuilder().ToString() == "<book" );
    }

    {
        std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
        std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

        assert( !xml_writer->Settings().OmitXmlDeclaration() );
        assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

        ASSERT_THROWS_EXCEPTION(System::Exception, xml_writer->WriteStartElement("book") );
    }
}

void Run()
{
    InitialXmlWriterState();
    WriteStartDocumentProducesDefaultProlog();
    WriteStartDocumentProducesPrologWithOmittedDeclaration();
    CallingWriteStartDocumentPutsWriteStateAtProlog();
    CanOnlyCallWriteStartDocumentOnceAndWhileWriteStateIsStart();
    CanCallWriteProcessingInstructionInsteadOfWriteStartDocument();
    CallingWriteProcessingInstructionWithEmptyNameThrowsException();
    CallingWriteStartDocumentProducesADefaultProlog();
    return;
    CallingWriteEndDocumentPutsXmlWriterBackInWriteStateOfStart();
    SettingOmitXmlDeclarationToTrueAllowsWriteStartElementToBeImmediatelyCalled();
}

}

int main(void)
{
    TestXmlTextWriter::Run();
    return EXIT_SUCCESS;
}