#include <cppdotnet/System/Xml/XmlNodeReader.hpp>

namespace System::Xml
{

const XmlReaderSettings &XmlNodeReader::Settings() const noexcept
{
    return _settings;
}

XmlReaderSettings &XmlNodeReader::Settings() noexcept
{
    return _settings;
}

bool XmlNodeReader::Read()
{
    return false;
}

}