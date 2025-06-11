#pragma once

#include <cstdint>
#include <cstddef>
#include <uuid/uuid.h>
#include "System/ReadOnlySpan.hpp"


namespace System
{

class Guid
{
public:
    constexpr Guid() = default;
    Guid(std::int32_t a, std::int16_t b, std::int16_t c,
         std::byte d, std::byte e, std::byte f, std::byte g, std::byte h, std::byte i, std::byte j, std::byte k);

    Guid(std::uint32_t a, std::uint16_t b, std::uint16_t c,
         std::byte d, std::byte e, std::byte f, std::byte g, std::byte h, std::byte i, std::byte j, std::byte k);

    Guid(ReadOnlySpan<std::byte> bytes);

    Guid(std::span<const std::byte> bytes)
        :
        // Delegating constructor...
        Guid( ReadOnlySpan<std::byte>(bytes) )
    {
    }
    
    Guid(const Guid &other);

    static Guid Empty();

    static Guid AllBitsSet();

    int Variant() const { return 0; }
    int Version() const { return 0; }

    ReadOnlySpan<std::byte, 16> ToByteArray() const;

    std::string ToString() const;

    static Guid NewGuid();
protected:
    uuid_t _data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};

}