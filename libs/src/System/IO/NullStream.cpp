#include "System/IO/NullStream.hpp"


namespace System::IO
{

void NullStream::Write(const std::string_view )
{
}

void NullStream::Write(ReadOnlySpan<std::byte> )
{
}

void NullStream::WriteByte(std::byte )
{
}

void NullStream::WriteByte(uint8_t )
{
}

std::string NullStream::Read(int )
{
    return { };
}

int NullStream::ReadByte()
{
    return 0;
}

void NullStream::_close()
{
}

void NullStream::_flush()
{
}

size_t NullStream::_length()
{
    return 0;
}

size_t NullStream::_position()
{
    return 0;
}

}