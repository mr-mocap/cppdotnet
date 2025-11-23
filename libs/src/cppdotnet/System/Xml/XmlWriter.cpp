#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/XmlTextWriter.hpp>
#include <cppdotnet/System/IO/FileStream.hpp>
#include <cppdotnet/System/IO/StreamWriter.hpp>
#include <cppdotnet/System/Exception.hpp>
#include <cppdotnet/System/Convert.hpp>
#include <cppdotnet/System/Private/private.hpp>

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

    WriteProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");

    POSTCONDITION( WriteState() == Xml::WriteState::Prolog );
}

void XmlWriter::WriteEndDocument()
{
    WriteState( Xml::WriteState::Start );

    POSTCONDITION( WriteState() == Xml::WriteState::Start );
}

void XmlWriter::WriteStartElement(std::string_view local_name)
{
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
    if ( WriteState() != Xml::WriteState::Start )
        ThrowWithTarget( ArgumentException( "WriteStartDocument() had already been called" ) );

    WriteState( Xml::WriteState::Prolog );
    WriteRaw( std::format("<?{} {}?>", name, text) );
}

void XmlWriter::WriteWhitespace(std::string_view ws)
{
    WriteValue( ws );
}

}