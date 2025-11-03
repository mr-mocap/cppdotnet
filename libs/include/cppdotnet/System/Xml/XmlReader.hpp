#pragma once

#include <cppdotnet/System/IO/TextReader.hpp>
#include <cppdotnet/System/IO/Stream.hpp>
#include <cppdotnet/System/Xml/XmlReaderSettings.hpp>
#include <cppdotnet/System/Xml/XmlReader.hpp>
#include <memory>

namespace System::Xml
{

class XmlReader
{
public:
    XmlReader() = default;
    virtual ~XmlReader() = default;

    virtual const XmlReaderSettings &Settings() const noexcept = 0;
    virtual       XmlReaderSettings &Settings()       noexcept = 0;

    virtual bool Read() = 0;

    static std::unique_ptr<XmlReader> Create(std::unique_ptr<System::IO::Stream> &&stream);
    static std::unique_ptr<XmlReader> Create(std::unique_ptr<System::IO::Stream> &&stream, XmlReaderSettings &&reader_settings);
    static std::unique_ptr<XmlReader> Create(std::unique_ptr<System::IO::TextReader> &&text_reader);
    static std::unique_ptr<XmlReader> Create(std::unique_ptr<System::IO::TextReader> &&text_reader, XmlReaderSettings &&reader_settings);
};

}