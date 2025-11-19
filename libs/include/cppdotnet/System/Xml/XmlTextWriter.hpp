#pragma once

#include <cppdotnet/System/Xml/XmlWriter.hpp>

namespace System::Xml
{

class XmlTextWriter : public XmlWriter
{
public:
    XmlTextWriter() = default;
    XmlTextWriter(std::unique_ptr<System::IO::TextWriter> &&text_writer);
   ~XmlTextWriter() override = default;

    const XmlWriterSettings &Settings() const noexcept override;
          XmlWriterSettings &Settings()       noexcept override;

protected:
    std::unique_ptr<System::IO::TextWriter> _text_writer;
    XmlWriterSettings _settings;
};

}