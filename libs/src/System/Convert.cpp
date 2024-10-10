#include "System/Convert.hpp"
#include "System/Boolean.hpp"
#include <format>

namespace System
{

const std::string_view Convert::ToString(bool value)
{
    if ( value )
        return Boolean::TrueString;
    else
        return Boolean::FalseString;
}

std::string Convert::ToString(char value)
{
    return std::string{ 1, value };
}

std::string Convert::ToString(float value)
{
    return std::format("{}", value);
}

std::string Convert::ToString(double value)
{
    return std::format("{}", value);
}

std::string Convert::ToString(int8_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(int16_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(int32_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(int64_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(uint8_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(uint16_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(uint32_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(uint64_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    return {};
}

const std::string_view Convert::ToString(Diagnostics::TraceLevel level)
{
    using namespace std::literals;

    const std::string_view levels[] = {
        "Off"sv,
        "Error"sv,
        "Warning"sv,
        "Info"sv,
        "Verbose"sv,
        "InvalidValue"sv
    };

    if ((level <= Diagnostics::TraceLevel::Off) || (level > Diagnostics::TraceLevel::Verbose))
        return levels[5];

    return levels[ static_cast<int>(level) ];
}

}