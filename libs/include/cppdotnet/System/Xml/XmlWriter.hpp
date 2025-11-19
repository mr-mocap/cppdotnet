#pragma once

#include <cppdotnet/System/DateTime.hpp>
#include <cppdotnet/System/DateTimeOffset.hpp>
#include <cppdotnet/System/IO/TextWriter.hpp>
#include <cppdotnet/System/IO/Stream.hpp>
#include <cppdotnet/System/Xml/XmlWriterSettings.hpp>
#include <memory>
#include <cstdint>
#include <string_view>

namespace System::Xml
{

class XmlWriter
{
public:
    XmlWriter() = default;
    virtual ~XmlWriter() = default;

    virtual const XmlWriterSettings &Settings() const noexcept = 0;
    virtual       XmlWriterSettings &Settings()       noexcept = 0;

    static std::unique_ptr<XmlWriter> Create(std::unique_ptr<System::IO::Stream> &&stream);
    static std::unique_ptr<XmlWriter> Create(std::unique_ptr<System::IO::Stream> &&stream, XmlWriterSettings &&reader_settings);
    static std::unique_ptr<XmlWriter> Create(std::unique_ptr<System::IO::TextWriter> &&text_reader);
    static std::unique_ptr<XmlWriter> Create(std::unique_ptr<System::IO::TextWriter> &&text_reader, XmlWriterSettings &&reader_settings);

    virtual void WriteValue(bool value);
    virtual void WriteValue(float value);
    virtual void WriteValue(double value);
    virtual void WriteValue(int32_t value);
    virtual void WriteValue(int64_t value);
    virtual void WriteValue(std::string_view value);
    virtual void WriteValue(DateTime value);
    virtual void WriteValue(DateTimeOffset value);

    virtual void WriteWhitespace(std::string_view ws);
};

}