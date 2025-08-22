#include "System/Environment.hpp"
#include <string>
#include <string_view>
#include <cstdint>
#include <format>

namespace System::IO
{

class TextWriter
{
public:
    TextWriter() = default;
    virtual ~TextWriter();

    std::string_view NewLine() const { return _newLine; }
    void NewLine(std::string_view new_value) { _newLine = new_value; }

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
    virtual void Write(std::string_view message) = 0;

    template <typename ...Args>
        requires (sizeof...(Args) > 0)
    inline void Write(std::format_string<Args...> fmt, Args &&... args)
    {
        // Let's use the more primitive Write(std::string_view) underneath
        Write( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

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
    virtual void WriteLine(std::string_view message);
    
    template <typename ...Args>
        requires (sizeof...(Args) > 0)
    inline void WriteLine(std::format_string<Args...> &&fmt, Args &&... args)
    {
        // Let's use the more primitive Write(std::string_view) underneath
        WriteLine( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

protected:
    std::string _newLine{ System::Environment::NewLine() };
};

}