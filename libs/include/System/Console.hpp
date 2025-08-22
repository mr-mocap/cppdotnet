#include <memory>
#include <format>
#include <string>
#include <string_view>
#include <cstdint>

namespace System
{

namespace IO
{
class TextReader;
class TextWriter;
class Stream;
}


class Console final
{
public:

    static IO::TextReader &In();
    static IO::TextWriter &Out();
    static IO::TextWriter &Error();
    static IO::TextWriter &Log();

    static void SetIn(std::unique_ptr<IO::TextReader>    new_input_reader);
    static void SetOut(std::unique_ptr<IO::TextWriter>   new_input_writer);
    static void SetError(std::unique_ptr<IO::TextWriter> new_input_writer);
    static void SetLog(std::unique_ptr<IO::TextWriter>   new_input_writer);

    static std::unique_ptr<IO::Stream> OpenStandardInput();
    static std::unique_ptr<IO::Stream> OpenStandardOutput();
    static std::unique_ptr<IO::Stream> OpenStandardError();
    static std::unique_ptr<IO::Stream> OpenStandardLog();

    static bool IsInputRedirected();
    static bool IsOutputRedirected();
    static bool IsErrorRedirected();

    static std::string ReadLine();

    static void Write(bool value);
    static void Write(char value);
    static void Write(int32_t value);
    static void Write(uint32_t value);
    static void Write(int64_t value);
    static void Write(uint64_t value);
    static void Write(float value);
    static void Write(double value);
    static void Write(std::string_view data);
    static void Write(const char *data)
    {
        // Let's use the more primitive Write(std::string_view) underneath
        Write( std::string_view(data) );
    }

    template <typename ...Args>
    static void Write(std::format_string<Args...> &&fmt, Args &&... args)
    {
        // Let's use the more primitive Write(std::string_view) underneath
        Write( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static void WriteLine();
    static void WriteLine(bool value);
    static void WriteLine(char value);
    static void WriteLine(int32_t value);
    static void WriteLine(uint32_t value);
    static void WriteLine(int64_t value);
    static void WriteLine(uint64_t value);
    static void WriteLine(float value);
    static void WriteLine(double value);
    static void WriteLine(std::string_view line);
    static void WriteLine(const char *line)
    {
        // Let's use the more primitive WriteLine(std::string_view) underneath
        WriteLine( std::string_view(line) );
    }

    template <typename ...Args>
    static void WriteLine(std::format_string<Args...> &&fmt, Args &&... args)
    {
        // Let's use the more primitive WriteLine(std::string_view) underneath
        WriteLine( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }
};

}
