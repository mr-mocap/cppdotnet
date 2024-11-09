#pragma once

#include "System/Diagnostics/SourceLevels.hpp"
#include "System/Diagnostics/TraceLevel.hpp"
#include "System/Diagnostics/TraceOptions.hpp"
#include "System/Exception.hpp"
#include "System/Base.hpp"
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <cstdint>
#include <cctype>
#include <cassert>
#include <charconv>

namespace System
{

class Convert
{
public:

    static const std::string_view ToString(bool value);
    static std::string      ToString(char value);
    static std::string      ToString(float  value);
    static std::string      ToString(double value);

    static std::string      ToString(int8_t  value, Base toBase = Base::Decimal);
    static std::string      ToString(int16_t value, Base toBase = Base::Decimal);
    static std::string      ToString(int32_t value, Base toBase = Base::Decimal);
    static std::string      ToString(int64_t value, Base toBase = Base::Decimal);

    static std::string      ToString(uint8_t  value, Base toBase = Base::Decimal);
    static std::string      ToString(uint16_t value, Base toBase = Base::Decimal);
    static std::string      ToString(uint32_t value, Base toBase = Base::Decimal);
    static std::string      ToString(uint64_t value, Base toBase = Base::Decimal);

    static const std::string_view ToString(Diagnostics::TraceLevel   value);
    static const std::string_view ToString(Diagnostics::TraceOptions value);
    static const std::string_view ToString(Diagnostics::SourceLevels value);

    static std::vector<std::byte> FromHexString(const std::string_view input_string); // Returns sequence as LITTLE-ENDIAN

    // From IConvertable  (move there)
    static Diagnostics::TraceLevel   ToType(const std::string_view value, Diagnostics::TraceLevel   this_is_here_to_select_the_correct_function);
    static Diagnostics::TraceOptions ToType(const std::string_view value, Diagnostics::TraceOptions this_is_here_to_select_the_correct_function);
    static Diagnostics::SourceLevels ToType(const std::string_view value, Diagnostics::SourceLevels this_is_here_to_select_the_correct_function);

    // C++ specific
    static std::string ToChars(auto ...format_args)
    {
        std::array<char, 32> buffer;

        std::to_chars_result result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), format_args...);

        if (result.ec == std::errc::value_too_large)
            ThrowWithTarget( ArgumentOutOfRangeException( "format_args" ) );

        assert( result.ec == std::errc() );

        return { buffer.data(), result.ptr - buffer.data() };
    }

    static std::byte From2HexCharsToByte(const std::string_view input_string);
};

}