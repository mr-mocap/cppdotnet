#pragma once

#include "System/Diagnostics/TraceOptions.hpp"
#include "System/Diagnostics/TraceFilter.hpp"
#include "System/Collections/Specialized/StringDictionary.hpp"
#include <string>
#include <format>
#include <string_view>
#include <memory>


namespace System::Diagnostics
{

class TraceListener
{
public:
    TraceListener();
    TraceListener(const std::string_view name);
    virtual ~TraceListener() = default;

    const std::string_view Name() const;
    void Name(const std::string &new_name) { _name = new_name; }
    void Name(const std::string_view new_name) { _name = new_name; }

    TraceOptions TraceOutputOptions() const { return _options; }
    void         TraceOutputOptions(TraceOptions new_options) { _options = new_options; }

    virtual bool IsThreadSafe() const;

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

    template <typename ...Args>
    void Write(std::format_string<Args...> &&fmt, Args &&... args)
    {
        Write( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    virtual void WriteLine(const std::string_view message) = 0;
    virtual void WriteLine(const std::string_view message, const std::string_view category) = 0;

    template <typename ...Args>
    void WriteLine(std::format_string<Args...> &&fmt, Args &&... args)
    {
        WriteLine( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    virtual void Fail(const std::string_view message) = 0;
    virtual void Fail(const std::string_view message, const std::string_view detail) = 0;

    virtual void WriteIndent() = 0;

    const Collections::Specialized::StringDictionary &Attributes() const { return _attributes; }

    const TraceFilter *Filter() const { return _filter.get(); }
          TraceFilter *Filter()       { return _filter.get(); }
    
    void Filter(std::unique_ptr<TraceFilter> &&moved_ptr) { _filter = std::move(moved_ptr); }
protected:
    std::string  _name;
    int          _indentLevel = 0;
    int          _indentSize  = 0;
    TraceOptions _options{ TraceOptions::None };
    bool         _needIndent = false;
    std::string  _indentString;
    Collections::Specialized::StringDictionary _attributes;
    std::unique_ptr<TraceFilter> _filter;

    void SetNeedIndent();
};

}
