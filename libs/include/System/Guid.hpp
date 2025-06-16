#pragma once

#include "System/ReadOnlySpan.hpp"
#include <cstdint>
#include <cstddef>
#include <string>
#include <string_view>
#include <compare>
#include <optional>
#include <uuid/uuid.h>


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
    Guid(std::string_view str_input);
    
    Guid(const Guid &other);

    Guid &operator =(const Guid &);

    static Guid Empty();

    static Guid AllBitsSet();

    int Variant() const { return 0; }
    int Version() const { return 0; }

    ReadOnlySpan<std::byte, 16> ToByteArray() const;

    std::string ToString() const;
    std::string ToString(std::string_view format) const;

    static Guid NewGuid();

    static Guid Parse(std::string_view input);
    static Guid Parse(ReadOnlySpan<char> input);

    static std::optional<Guid> TryParse(std::string_view input);
    static std::optional<Guid> TryParse(ReadOnlySpan<char> input);

    std::strong_ordering operator <=>(const Guid &other) const;

protected:
    uuid_t _data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    Guid(const uuid_t &external_value)
    {
        std::ranges::copy( std::span(external_value),
                           std::ranges::begin(_data) );
    }
};

}