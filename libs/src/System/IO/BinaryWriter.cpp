#include "System/IO/BinaryWriter.hpp"
#include <bit>


namespace System::IO
{

void BinaryWriter::Close()
{
    _stream->Close();
}

void BinaryWriter::Flush()
{
    _stream->Flush();
}

long BinaryWriter::Seek(long offset, SeekOrigin origin)
{
    return _stream->Seek( offset, origin );
}

void BinaryWriter::Write(std::byte value)
{
    _stream->WriteByte( value );
}

void BinaryWriter::Write(ReadOnlySpan<std::byte> values)
{
    _stream->Write( values );
}

void BinaryWriter::Write(char value)
{
    _stream->WriteByte( std::byte(value) );
}

void BinaryWriter::Write(bool value)
{
    _stream->WriteByte( value ? std::byte{ 1 } : std::byte{ 0 } );
}

void BinaryWriter::Write(std::int16_t value)
{
    _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(std::int32_t value)
{
    _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(std::int64_t value)
{
    _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(std::uint16_t value)
{
    _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(std::uint32_t value)
{
    _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(std::uint64_t value)
{
    _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(float value)
{
    _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(double value)
{
    _stream->Write( ReadOnlySpan(value).as_bytes() );
}

}