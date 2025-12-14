#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/XmlTextWriter.hpp>
#include <cppdotnet/System/Xml/XmlComment.hpp>
#include <cppdotnet/System/Xml/XmlDeclaration.hpp>
#include <cppdotnet/System/Xml/XmlProcessingInstruction.hpp>
#include <cppdotnet/System/Xml/XmlWhitespace.hpp>
#include <cppdotnet/System/IO/FileStream.hpp>
#include <cppdotnet/System/IO/StreamWriter.hpp>
#include <cppdotnet/System/Exception.hpp>
#include <cppdotnet/System/Convert.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>
#include <cppdotnet/System/Xml/Private/Utils.hpp>

namespace System::Xml
{

std::unique_ptr<XmlWriter> XmlWriter::Create(std::string_view filename)
{
    std::unique_ptr<IO::Stream> file_stream = std::make_unique<IO::FileStream>( filename );

    // TODO: Check for errors here

    auto writer = std::make_unique<XmlTextWriter>( std::move(file_stream) );

    return writer;
}

std::unique_ptr<XmlWriter> XmlWriter::Create(std::unique_ptr<System::IO::Stream> &&stream)
{
    auto writer = std::make_unique<XmlTextWriter>( std::move( stream ) );

    return writer;
}

std::unique_ptr<XmlWriter> XmlWriter::Create(std::unique_ptr<System::IO::Stream> &&stream, const XmlWriterSettings &writer_settings)
{
    auto writer = std::make_unique<XmlTextWriter>( std::move( stream ) );
    
    writer->Settings() = writer_settings;
    return writer;
}

std::unique_ptr<XmlWriter> XmlWriter::Create(std::unique_ptr<System::IO::TextWriter> &&text_writer)
{
    auto writer = std::make_unique<XmlTextWriter>( std::move( text_writer ) );
    
    return writer;
}

std::unique_ptr<XmlWriter> XmlWriter::Create(std::shared_ptr<System::IO::TextWriter> text_writer)
{
    auto writer = std::make_unique<XmlTextWriter>( text_writer );
    
    return writer;
}

std::unique_ptr<XmlWriter> XmlWriter::Create(std::unique_ptr<System::IO::TextWriter> &&text_writer, const XmlWriterSettings &writer_settings)
{
    auto writer = std::make_unique<XmlTextWriter>( std::move( text_writer ) );
    
    writer->Settings() = std::move( writer_settings );
    return writer;
}

std::unique_ptr<XmlWriter> XmlWriter::Create(std::shared_ptr<System::IO::TextWriter> text_writer, const XmlWriterSettings &writer_settings)
{
    auto writer = std::make_unique<XmlTextWriter>( text_writer );
    
    writer->Settings() = writer_settings;
    return writer;
}

void XmlWriter::WriteValue(DateTime value)
{
    WriteValue( value.ToString() );
}

void XmlWriter::WriteValue(DateTimeOffset value)
{
    UNUSED( value );

    // TODO: Implement Me
}

void XmlWriter::WriteStartDocument()
{
    if ( WriteState() != Xml::WriteState::Start )
        ThrowWithTarget( InvalidOperationException() );

    if ( Settings().OmitXmlDeclaration() == true )
    {
        WriteState( Xml::WriteState::Prolog );
        return;
    }

    ASSERT( WriteState() == Xml::WriteState::Start );

    XmlDeclaration xml_declaration( "1.0", "UTF-8", nullptr );

    xml_declaration.WriteTo( *this );

    POSTCONDITION( WriteState() == Xml::WriteState::Prolog );
}

void XmlWriter::WriteEndDocument()
{
    WriteState( Xml::WriteState::Start );

    POSTCONDITION( WriteState() == Xml::WriteState::Start );
}

void XmlWriter::WriteStartElement(std::string_view local_name)
{
    if ( local_name.empty() )
        ThrowWithTarget( ArgumentException( "Argument is empty", "local_name" ) );

    if ( WriteState() == Xml::WriteState::Start )
        WriteStartDocument();

    WriteState( Xml::WriteState::Element );
    WriteRaw( std::format("<{}", local_name) );

    POSTCONDITION( WriteState() == Xml::WriteState::Element );
}

void XmlWriter::WriteEndElement()
{
}

void XmlWriter::WriteStartAttribute(std::string_view local_name)
{
    UNUSED( local_name );
}

void XmlWriter::WriteEndAttribute()
{
}

void XmlWriter::WriteProcessingInstruction(std::string_view name, std::string_view text)
{
    if ( name.empty() )
        ThrowWithTarget( ArgumentException( "Argument is empty", "name" ) );

    if ( WriteState() == Xml::WriteState::Start )
        WriteStartDocument();

    ASSERT( WriteState() != Xml::WriteState::Start );

    Xml::WriteState entry_state = WriteState();

    XmlProcessingInstruction xml_processing_instruction( name, text, nullptr );

    xml_processing_instruction.WriteTo( *this );

    POSTCONDITION( WriteState() == entry_state );
}

void XmlWriter::WriteComment(std::string_view comment)
{
    if ( WriteState() == Xml::WriteState::Start )
        WriteStartDocument();

    ASSERT( WriteState() != Xml::WriteState::Start );

    Xml::WriteState entry_state = WriteState();

    XmlComment xml_comment( comment, nullptr );

    xml_comment.WriteTo( *this );

    POSTCONDITION( WriteState() == entry_state );
}

void XmlWriter::WriteWhitespace(std::string_view ws)
{
    if ( WriteState() == Xml::WriteState::Start )
        WriteStartDocument();

    ASSERT( WriteState() != Xml::WriteState::Start );

    Xml::WriteState entry_state = WriteState();

    XmlWhitespace xml_whitespace( ws, nullptr );

    xml_whitespace.WriteTo( *this );

    POSTCONDITION( WriteState() == entry_state );
}

}