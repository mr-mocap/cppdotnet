#pragma once

#include "System/Diagnostics/TraceLevel.hpp"
#include "System/Base.hpp"
#include <string>
#include <string_view>
#include <cstdint>

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

    static const std::string_view ToString(Diagnostics::TraceLevel value);
};

}