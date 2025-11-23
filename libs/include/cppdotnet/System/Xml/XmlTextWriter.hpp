#pragma once

#include <cppdotnet/System/Xml/XmlWriter.hpp>

namespace System::Xml
{

class XmlTextWriter : public XmlWriter
{
public:
    XmlTextWriter() = delete;
    XmlTextWriter(std::shared_ptr<System::IO::TextWriter> text_writer);
    XmlTextWriter(std::unique_ptr<System::IO::TextWriter> &&text_writer);
    XmlTextWriter(std::unique_ptr<System::IO::Stream> &&stream);
   ~XmlTextWriter() override = default;

    const XmlWriterSettings &Settings() const noexcept override;
          XmlWriterSettings &Settings()       noexcept override;

    void WriteValue(bool value) override;
    void WriteValue(float value) override;
    void WriteValue(double value) override;
    void WriteValue(int32_t value) override;
    void WriteValue(int64_t value) override;
    void WriteValue(std::string_view value) override;

    void WriteString(std::string_view data) override;

    void WriteRaw(std::string_view data) override;

    System::Xml::WriteState WriteState() const override;

    void Close() override;

    System::IO::Stream *BaseStream();
protected:
    std::shared_ptr<System::IO::TextWriter> _text_writer;
    XmlWriterSettings       _settings;
    System::Xml::WriteState _write_state = WriteState::Start;

    void WriteState(System::Xml::WriteState new_state) override;
};

}