#include <cstdlib>
#include <cassert>
#include <cppdotnet/System/Xml/XmlTextWriter.hpp>
#include <cppdotnet/System/IO/StringWriter.hpp>

namespace TestXmlTextWriter
{

void InitialXmlWriterState()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( string_writer->GetStringBuilder().Length() == 0 );
    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );
}

void CanOnlyCallWriteStartDocumentOnceAndWhileWriteStateIsStart()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

    xml_writer->WriteStartDocument();

    assert( xml_writer->WriteState() != System::Xml::WriteState::Start );

    try
    {
        xml_writer->WriteStartDocument();
        assert( false );  // Shouldn't get here
    }
    catch(const System::SystemException &e)
    {
        assert( true );
    }
    
}

void CallingWriteStartDocumentPutsWriteStateAtProlog()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

    xml_writer->WriteStartDocument();

    assert( xml_writer->WriteState() == System::Xml::WriteState::Prolog );
}

void CanCallWriteProcessingInstructionInsteadOfWriteStartDocument()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

    std::string_view name = "xml";
    std::string_view value = "attributes go here";

    xml_writer->WriteProcessingInstruction(name, value);

    assert( xml_writer->WriteState() == System::Xml::WriteState::Prolog );

    assert( string_writer->GetStringBuilder().ToString() == "<?xml attributes go here?>" );
}

void CallingWriteProcessingInstructionWithEmptyNameThrowsException()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

    try
    {
        xml_writer->WriteProcessingInstruction("", "Some Text");
        assert( false );
    }
    catch(const System::ArgumentException &)
    {
        assert( true );
    }
    
}

void CanOnlyCallWriteProcessingInstructionIfWriteStateIsStart()
{
    std::shared_ptr<System::IO::StringWriter> string_writer = std::make_shared<System::IO::StringWriter>();
    std::unique_ptr<System::Xml::XmlWriter> xml_writer = System::Xml::XmlWriter::Create( string_writer );

    assert( xml_writer->WriteState() == System::Xml::WriteState::Start );

    xml_writer->WriteProcessingInstruction("xml", "some attributes");

    assert( xml_writer->WriteState() == System::Xml::WriteState::Prolog );

    try
    {
        xml_writer->WriteProcessingInstruction("stuff", "more attributes");
        assert( false );
    }
    catch(const System::ArgumentException &)
    {
        assert( true );
    }
    
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

        try
        {
            xml_writer->WriteStartElement("book");
            assert( false );
        }
        catch(const std::exception& e)
        {
            assert( true );
        }
    }
}

void Run()
{
    return;
    InitialXmlWriterState();
    CanOnlyCallWriteStartDocumentOnceAndWhileWriteStateIsStart();
    CallingWriteStartDocumentPutsWriteStateAtProlog();
    CanCallWriteProcessingInstructionInsteadOfWriteStartDocument();
    CallingWriteProcessingInstructionWithEmptyNameThrowsException();
    CanOnlyCallWriteProcessingInstructionIfWriteStateIsStart();
    CallingWriteStartDocumentProducesADefaultProlog();
    CallingWriteEndDocumentPutsXmlWriterBackInWriteStateOfStart();
    SettingOmitXmlDeclarationToTrueAllowsWriteStartElementToBeImmediatelyCalled();
}

}

int main(void)
{
    TestXmlTextWriter::Run();
    return EXIT_SUCCESS;
}