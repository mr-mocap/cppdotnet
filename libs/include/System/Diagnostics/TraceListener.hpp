#include "System/Diagnostics/TraceOptions.hpp"
#include "System/Diagnostics/TraceFilter.hpp"
#include "System/Diagnostics/TraceEventCache.hpp"
#include "System/Collections/Specialized/StringDictionary.hpp"
#include <string>
#include <string_view>
#include <format>
#include <memory>
#include <concepts>


namespace System::Diagnostics
{

class TraceListener
{
public:
    TraceListener();
    TraceListener(std::string_view name);
    virtual ~TraceListener() = default;

    std::string_view Name() const;
    void Name(const std::string &new_name) { _name = new_name; }
    void Name(std::string_view new_name) { _name = new_name; }

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

    virtual void Write(std::string_view message) = 0;
    virtual void Write(std::string_view message, std::string_view category) = 0;

    template <typename T, typename ...Args>
        requires (!std::convertible_to<T, std::string_view> || sizeof...(Args) > 0)
    void Write(std::format_string<T, Args...> &&fmt, T &&arg1, Args &&... args)
    {
        Write( std::string_view( std::vformat( fmt.get(), std::make_format_args( arg1, args... ) ) ) );
    }

    virtual void WriteLine(std::string_view message) = 0;
    virtual void WriteLine(std::string_view message, std::string_view category) = 0;

    template <typename T, typename ...Args>
        requires (!std::convertible_to<T, std::string_view> || sizeof...(Args) > 0)
    void WriteLine(std::format_string<T, Args...> &&fmt, T &&arg1, Args &&... args)
    {
        WriteLine( std::string_view( std::vformat( fmt.get(), std::make_format_args( arg1, args... ) ) ) );
    }

    virtual void Fail(std::string_view message) = 0;
    virtual void Fail(std::string_view message, std::string_view detail) = 0;

    template <typename T, typename ...Args>
        requires (!std::convertible_to<T, std::string_view> || sizeof...(Args) > 0)
    void Fail(std::format_string<T, Args...> &&fmt, T &&arg1, Args &&... args)
    {
        Fail( std::string_view( std::vformat( fmt.get(), std::make_format_args( arg1, args... ) ) ) );
    }

    virtual void WriteIndent() = 0;

    virtual void TraceData(System::Diagnostics::TraceEventCache &event_cache,
                                               std::string_view  source,
                            System::Diagnostics::TraceEventType  event_type,
                                                            int  id
                          );

    virtual void TraceData(System::Diagnostics::TraceEventCache &event_cache,
                                               std::string_view  source,
                            System::Diagnostics::TraceEventType  event_type,
                                                            int  id,
                                               std::string_view  message
                          );

    template <typename ...Args>
    void TraceData(System::Diagnostics::TraceEventCache  &event_cache,
                                       std::string_view   source,
                    System::Diagnostics::TraceEventType   event_type,
                                                    int   id,
                            std::format_string<Args...> &&fmt,
                                                   Args &&... args)
    {
        TraceData( event_cache,
                   source,
                   event_type,
                   id,
                   std::string_view( std::vformat( fmt.get(), std::make_wformat_args( args... ) ) )
                 );
    }

    const Collections::Specialized::StringDictionary &Attributes() const { return _attributes; }

    //?? GetSupportedAttributes() const;

    const TraceFilter *Filter() const { return _filter.get(); }
          TraceFilter *Filter()       { return _filter.get(); }
    
    void Filter(std::unique_ptr<TraceFilter> &&moved_ptr) { _filter = std::move(moved_ptr); }
protected:
    std::string  _name;
    int          _indentLevel = 0;
    int          _indentSize  = 0;
    TraceOptions _options     = TraceOptions::None;
    bool         _needIndent  = false;
    std::string  _indentString;
    Collections::Specialized::StringDictionary _attributes;
    std::unique_ptr<TraceFilter> _filter;

    void SetNeedIndent();
};

}
