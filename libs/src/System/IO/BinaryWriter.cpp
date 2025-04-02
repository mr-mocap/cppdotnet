#include "System/IO/BinaryWriter.hpp"
#include <bit>


namespace System::IO
{

void BinaryWriter::Close()
{
    if ( OutStream() )
        _stream->Close();
}

void BinaryWriter::Flush()
{
    if ( OutStream() )
        _stream->Flush();
}

long BinaryWriter::Seek(long offset, SeekOrigin origin)
{
    if ( OutStream() )
        return _stream->Seek( offset, origin );
    return 0;
}

void BinaryWriter::Write(std::byte value)
{
    if ( OutStream() )
        _stream->WriteByte( value );
}

void BinaryWriter::Write(ReadOnlySpan<std::byte> values)
{
    if ( OutStream() )
        _stream->Write( values );
}

void BinaryWriter::Write(char value)
{
    if ( OutStream() )
        _stream->WriteByte( std::byte(value) );
}

void BinaryWriter::Write(bool value)
{
    if ( OutStream() )
        _stream->WriteByte( value ? std::byte{ 1 } : std::byte{ 0 } );
}

void BinaryWriter::Write(std::int16_t value)
{
    if ( OutStream() )
        _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(std::int32_t value)
{
    if ( OutStream() )
        _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(std::int64_t value)
{
    if ( OutStream() )
        _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(std::uint16_t value)
{
    if ( OutStream() )
        _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(std::uint32_t value)
{
    if ( OutStream() )
        _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(std::uint64_t value)
{
    if ( OutStream() )
        _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(float value)
{
    if ( OutStream() )
        _stream->Write( ReadOnlySpan(value).as_bytes() );
}

void BinaryWriter::Write(double value)
{
    if ( OutStream() )
        _stream->Write( ReadOnlySpan(value).as_bytes() );
}

}