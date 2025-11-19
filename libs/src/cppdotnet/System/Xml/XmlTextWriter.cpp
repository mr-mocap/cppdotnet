#include <cppdotnet/System/Xml/XmlTextWriter.hpp>

namespace System::Xml
{

XmlTextWriter::XmlTextWriter(std::unique_ptr<System::IO::TextWriter> &&text_writer)
    :
    _text_writer( std::move(text_writer) )
{
}

const XmlWriterSettings &XmlTextWriter::Settings() const noexcept
{
    return _settings;
}

XmlWriterSettings &XmlTextWriter::Settings() noexcept
{
    return _settings;
}

}