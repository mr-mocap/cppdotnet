#include <cppdotnet/System/Xml/XmlReader.hpp>
#include <cppdotnet/System/Xml/XmlTextReader.hpp>

namespace System::Xml
{

XmlTextReader::XmlTextReader(std::unique_ptr<System::IO::TextReader> &&text_reader)
    :
    _text_reader( std::move(text_reader) )
{
}

const XmlReaderSettings &XmlTextReader::Settings() const noexcept
{
    return _settings;
}

XmlReaderSettings &XmlTextReader::Settings() noexcept
{
    return _settings;
}

bool XmlTextReader::Read()
{
    return false; // TODO: Implement Me!
}

}