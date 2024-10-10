#pragma once

#include "System/Diagnostics/TraceOptions.hpp"
#include <string>
#include <string_view>


namespace System::Diagnostics
{

class TraceListener
{
public:
    TraceListener();
    TraceListener(const std::string_view name);

    const std::string_view Name() const;

    TraceOptions TraceOutputOptions() const { return _options; }
    void         TraceOutputOptions(TraceOptions new_options) { _options = new_options; }

    bool NeedIndent() const;
    void NeedIndent(bool new_value) { _needIndent = new_value; }

    int  IndentLevel() const;
    void IndentLevel(int new_level);

    int  IndentSize() const;
    void IndentSize(int new_size);

    virtual void Close() = 0;
    virtual void Flush() = 0;

    virtual void Write(const std::string_view message) = 0;
    virtual void Write(const std::string_view message, const std::string_view category) = 0;

    virtual void WriteLine(const std::string_view message) = 0;
    virtual void WriteLine(const std::string_view message, const std::string_view category) = 0;

    virtual void Fail(const std::string_view message) = 0;
    virtual void Fail(const std::string_view message, const std::string_view detail) = 0;

    virtual void WriteIndent() = 0;
protected:
    std::string  _name;
    int          _indentLevel = 0;
    int          _indentSize  = 0;
    TraceOptions _options{ TraceOptions::None };
    bool         _needIndent = false;
    std::string  _indentString;

    void SetNeedIndent();
};

}
