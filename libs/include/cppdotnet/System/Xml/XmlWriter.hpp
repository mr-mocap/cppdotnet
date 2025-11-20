#pragma once

#include <cppdotnet/System/DateTime.hpp>
#include <cppdotnet/System/DateTimeOffset.hpp>
#include <cppdotnet/System/IO/TextWriter.hpp>
#include <cppdotnet/System/IO/Stream.hpp>
#include <cppdotnet/System/Xml/XmlWriterSettings.hpp>
#include <cppdotnet/System/Xml/WriteState.hpp>
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

    virtual void WriteValue(bool value) = 0;
    virtual void WriteValue(float value) = 0;
    virtual void WriteValue(double value) = 0;
    virtual void WriteValue(int32_t value) = 0;
    virtual void WriteValue(int64_t value) = 0;
    virtual void WriteValue(std::string_view value) = 0;
    virtual void WriteValue(DateTime value);
    virtual void WriteValue(DateTimeOffset value);

    virtual void WriteWhitespace(std::string_view ws);

    virtual void Close() = 0;

    virtual System::Xml::WriteState WriteState() const = 0;
};

}