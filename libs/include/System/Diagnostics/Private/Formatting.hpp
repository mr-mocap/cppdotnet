#include <format>
#include <string>
#include <string_view>

namespace System::Diagnostics
{
    struct FormatTag {}; // Experimental tag to differentiate between format strings and regular strings

    struct FormatCall
    {
        template <typename ...Args>
        FormatCall(std::format_string<Args...> &&fmt, Args &&... args)
            :
            s( std::vformat(fmt.get(), std::make_format_args(args...)) )
        {
        }

        operator std::string_view() const
        {
            return std::string_view(s);
        }
        std::string s;
    };

}