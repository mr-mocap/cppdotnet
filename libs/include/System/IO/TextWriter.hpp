#pragma once

#include "System/Environment.hpp"
#include <string>
#include <string_view>
#include <cstdint>

namespace System::IO
{

class TextWriter
{
public:
    TextWriter() = default;
    virtual ~TextWriter();

    const std::string_view NewLine() const { return _newLine; }
    void NewLine(const std::string_view new_value) { _newLine = new_value; }

    virtual void Close();
    virtual void Flush();

    virtual void Write(bool value);
    virtual void Write(char value) = 0;
    virtual void Write(int16_t value);
    virtual void Write(uint16_t value);
    virtual void Write(int32_t value);
    virtual void Write(uint32_t value);
    virtual void Write(int64_t value);
    virtual void Write(uint64_t value);
    virtual void Write(float value);
    virtual void Write(double value);
    virtual void Write(const std::string_view message) = 0;

    virtual void WriteLine(bool value);
    virtual void WriteLine(char value);
    virtual void WriteLine(int16_t value);
    virtual void WriteLine(uint16_t value);
    virtual void WriteLine(int32_t value);
    virtual void WriteLine(uint32_t value);
    virtual void WriteLine(int64_t value);
    virtual void WriteLine(uint64_t value);
    virtual void WriteLine(float value);
    virtual void WriteLine(double value);
    virtual void WriteLine(const std::string_view message);

protected:
    std::string _newLine{ System::Environment::NewLine() };
};

}