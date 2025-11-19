#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/XmlTextWriter.hpp>
#include <cppdotnet/System/IO/StreamWriter.hpp>
#include <cppdotnet/System/Private/private.hpp>

namespace System::Xml
{

std::unique_ptr<XmlWriter> XmlWriter::Create(std::unique_ptr<System::IO::Stream> &&stream)
{
    auto stream_writer = std::make_unique<System::IO::StreamWriter>( std::move( stream ) );
    auto writer = std::make_unique<XmlTextWriter>( std::move( stream_writer ) );
    
    return writer;
}

std::unique_ptr<XmlWriter> XmlWriter::Create(std::unique_ptr<System::IO::Stream> &&stream, XmlWriterSettings &&writer_settings)
{
    auto stream_writer = std::make_unique<System::IO::StreamWriter>( std::move( stream ) );
    auto writer = std::make_unique<XmlTextWriter>( std::move( stream_writer ) );
    
    writer->Settings() = std::move( writer_settings );
    return writer;
}

std::unique_ptr<XmlWriter> XmlWriter::Create(std::unique_ptr<System::IO::TextWriter> &&text_writer)
{
    auto writer = std::make_unique<XmlTextWriter>( std::move( text_writer ) );
    
    return writer;
}

std::unique_ptr<XmlWriter> XmlWriter::Create(std::unique_ptr<System::IO::TextWriter> &&text_writer, XmlWriterSettings &&writer_settings)
{
    auto writer = std::make_unique<XmlTextWriter>( std::move( text_writer ) );
    
    writer->Settings() = std::move( writer_settings );
    return writer;
}

void XmlWriter::WriteValue(bool value)
{
    UNUSED( value );

    // TODO: Implement Me
}

void XmlWriter::WriteValue(float value)
{
    UNUSED( value );

    // TODO: Implement Me
}

void XmlWriter::WriteValue(double value)
{
    UNUSED( value );

    // TODO: Implement Me
}

void XmlWriter::WriteValue(int32_t value)
{
    UNUSED( value );

    // TODO: Implement Me
}

void XmlWriter::WriteValue(int64_t value)
{
    UNUSED( value );

    // TODO: Implement Me
}

void XmlWriter::WriteValue(std::string_view value)
{
    UNUSED( value );

    // TODO: Implement Me
}

void XmlWriter::WriteValue(DateTime value)
{
    UNUSED( value );

    // TODO: Implement Me
}

void XmlWriter::WriteValue(DateTimeOffset value)
{
    UNUSED( value );

    // TODO: Implement Me
}

void WriteWhitespace(std::string_view ws)
{
    UNUSED( ws );

    // TODO: Implement Me
}

}