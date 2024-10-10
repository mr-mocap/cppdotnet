#pragma once

#include "System/IO/TextWriter.hpp"
#include "System/IO/StringBuilder.hpp"

namespace System::IO
{

class StringWriter : public TextWriter
{
public:
    StringWriter();
   ~StringWriter();

    const StringBuilder &GetStringBuilder() const { return _builder; }

    using TextWriter::Write;

    void Write(char value) override;
    void Write(const std::string_view message) override;

protected:
    StringBuilder _builder;
};

}