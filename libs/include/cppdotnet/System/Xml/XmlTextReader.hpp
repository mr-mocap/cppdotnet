#pragma once

#include <cppdotnet/System/Xml/XmlReader.hpp>

namespace System::Xml
{

class XmlTextReader : public XmlReader
{
public:
    XmlTextReader() = default;
    XmlTextReader(std::unique_ptr<System::IO::TextReader> &&text_reader);
   ~XmlTextReader() override = default;

    const XmlReaderSettings &Settings() const noexcept override;
          XmlReaderSettings &Settings()       noexcept override;

    bool Read() override;
protected:
    std::unique_ptr<System::IO::TextReader> _text_reader;
    XmlReaderSettings _settings;
};

}