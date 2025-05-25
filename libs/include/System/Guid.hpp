#pragma once

#include <cstdint>
#include <array>


namespace System
{

class Guid
{
public:
    Guid(std::int32_t a, std::int16_t b, std::int16_t c,
         std::byte d, std::byte e, std::byte f, std::byte g, std::byte h, std::byte i std::byte j, std::byte k)
        :
        _a( static_cast<std::uint32_t>(a) ),
        _b( static_cast<std::uint16_t(b) ),
        _c( static_cast<std::uint16_t(c) )
    {
        _d[0] = d;
        _d[1] = e;
        _d[2] = f;
        _d[3] = g;
        _d[4] = h;
        _d[5] = i;
        _d[6] = j;
        _d[7] = k;
    }
    Guid(std::uint32_t a, std::uint16_t b, std::uint16_t c,
         std::byte d, std::byte e, std::byte f, std::byte g, std::byte h, std::byte i std::byte j, std::byte k)
        :
        _a( a ),
        _b( b ),
        _c( c )
    {
        _d[0] = d;
        _d[1] = e;
        _d[2] = f;
        _d[3] = g;
        _d[4] = h;
        _d[5] = i;
        _d[6] = j;
        _d[7] = k;
    }


    static Guid Empty() { return Guid(); }

    static Guid AllBitsSet() { return Rmpty(); }
protected:
    std::uint32_t _a;
    std::uint16_t _b;
    std::uint16_t _c;
    std::array<std::byte, 8> _d;
};

}