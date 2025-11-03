#include <cppdotnet/System/Xml/XmlReader.hpp>
#include <cppdotnet/System/Xml/XmlTextReader.hpp>
#include <cppdotnet/System/IO/StreamReader.hpp>

namespace System::Xml
{

std::unique_ptr<XmlReader> XmlReader::Create(std::unique_ptr<System::IO::Stream> &&stream)
{
    auto stream_reader = std::make_unique<System::IO::StreamReader>( std::move( stream ) );
    auto reader = std::make_unique<XmlTextReader>( std::move( stream_reader ) );
    
    return reader;
}

std::unique_ptr<XmlReader> XmlReader::Create(std::unique_ptr<System::IO::Stream> &&stream, XmlReaderSettings &&reader_settings)
{
    auto stream_reader = std::make_unique<System::IO::StreamReader>( std::move( stream ) );
    auto reader = std::make_unique<XmlTextReader>( std::move( stream_reader ) );
    
    reader->Settings() = std::move( reader_settings );
    return reader;
}

std::unique_ptr<XmlReader> XmlReader::Create(std::unique_ptr<System::IO::TextReader> &&text_reader)
{
    auto reader = std::make_unique<XmlTextReader>( std::move( text_reader ) );
    
    return reader;
}

std::unique_ptr<XmlReader> XmlReader::Create(std::unique_ptr<System::IO::TextReader> &&text_reader, XmlReaderSettings &&reader_settings)
{
    auto reader = std::make_unique<XmlTextReader>( std::move( text_reader ) );
    
    reader->Settings() = std::move( reader_settings );
    return reader;
}

}