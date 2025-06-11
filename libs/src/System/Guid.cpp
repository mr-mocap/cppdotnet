#include "System/Guid.hpp"
#include "System/BitConverter.hpp"
#include "System/Span.hpp"
#include <algorithm>
#include <uuid/uuid.h>


namespace System
{

Guid::Guid(std::int32_t a, std::int16_t b, std::int16_t c,
           std::byte d, std::byte e, std::byte f, std::byte g, std::byte h, std::byte i, std::byte j, std::byte k)
{
    auto put_iter = std::begin(_data);

    for (std::byte i : BitConverter::GetBytes(a))
        *put_iter++ = static_cast<unsigned char>(i);
    for (std::byte i : BitConverter::GetBytes(b))
        *put_iter++ = static_cast<unsigned char>(i);
    for (std::byte i : BitConverter::GetBytes(c))
        *put_iter++ = static_cast<unsigned char>(i);
    
    *put_iter++ = static_cast<unsigned char>(d);
    *put_iter++ = static_cast<unsigned char>(e);
    *put_iter++ = static_cast<unsigned char>(f);
    *put_iter++ = static_cast<unsigned char>(g);
    *put_iter++ = static_cast<unsigned char>(h);
    *put_iter++ = static_cast<unsigned char>(i);
    *put_iter++ = static_cast<unsigned char>(j);
    *put_iter++ = static_cast<unsigned char>(k);
}

Guid::Guid(std::uint32_t a, std::uint16_t b, std::uint16_t c,
           std::byte d, std::byte e, std::byte f, std::byte g, std::byte h, std::byte i, std::byte j, std::byte k)
{
    auto put_iter = std::begin(_data);

    for (std::byte i : BitConverter::GetBytes(a))
        *put_iter++ = static_cast<unsigned char>(i);
    for (std::byte i : BitConverter::GetBytes(b))
        *put_iter++ = static_cast<unsigned char>(i);
    for (std::byte i : BitConverter::GetBytes(c))
        *put_iter++ = static_cast<unsigned char>(i);
    
    *put_iter++ = static_cast<unsigned char>(d);
    *put_iter++ = static_cast<unsigned char>(e);
    *put_iter++ = static_cast<unsigned char>(f);
    *put_iter++ = static_cast<unsigned char>(g);
    *put_iter++ = static_cast<unsigned char>(h);
    *put_iter++ = static_cast<unsigned char>(i);
    *put_iter++ = static_cast<unsigned char>(j);
    *put_iter++ = static_cast<unsigned char>(k);
}

Guid::Guid(ReadOnlySpan<std::byte> bytes)
{
    bytes.CopyTo( std::as_writable_bytes( std::span(_data) ) );
}

Guid::Guid(const Guid &other)
{
    uuid_copy( _data, other._data );
}

ReadOnlySpan<std::byte, 16> Guid::ToByteArray() const
{
    return ReadOnlySpan<std::byte, 16>( std::as_bytes( std::span(_data) ) );
}

Guid Guid::NewGuid()
{
    uuid_t uuid;

    uuid_generate( uuid );
    return Guid( std::as_bytes( std::span(uuid) ) );
}

Guid Guid::Empty()
{
    return Guid( std::as_bytes( std::span( std::initializer_list<unsigned char>{0, 0, 0, 0,
                                                                                0, 0, 0, 0,
                                                                                0, 0, 0, 0,
                                                                                0, 0, 0, 0} ) ) );
}

Guid Guid::AllBitsSet()
{
    return Guid( std::as_bytes( std::span( std::initializer_list<unsigned char>{0xFF, 0xFF, 0xFF, 0xFF,
                                                                                0xFF, 0xFF, 0xFF, 0xFF,
                                                                                0xFF, 0xFF, 0xFF, 0xFF,
                                                                                0xFF, 0xFF, 0xFF, 0xFF} ) ) );
}

std::string Guid::ToString() const
{
    char buffer[37];

    uuid_unparse( _data, buffer );
    return std::string( buffer );
}

}