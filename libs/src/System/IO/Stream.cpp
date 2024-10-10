#include "System/IO/Stream.hpp"


namespace System::IO
{

Stream::Stream(std::unique_ptr<std::iostream> &&stream, bool can_read, bool can_write)
    :
    _stream{ std::move(stream) },
    _canRead{ can_read },
    _canWrite{ can_write }
{
}

void Stream::Close()
{
}

void Stream::Flush()
{
    if ( _stream )
        _stream->flush();
}

void Stream::Write(const std::string_view bytes)
{
    if ( _stream && CanWrite() )
        _stream->write( bytes.data(), bytes.size() );
}

void Stream::WriteByte(const uint8_t byte)
{
    if ( _stream && CanWrite() )
        _stream->put( byte );
}

std::string Stream::Read(int number_of_bytes)
{
    if ( _stream && CanRead() )
    {
        std::string input_buffer;

        input_buffer.resize( number_of_bytes );
        _stream->read( input_buffer.data(), number_of_bytes );
        return input_buffer;
    }
    return {};
}

int Stream::ReadByte()
{
    if ( _stream && CanRead() )
        return _stream->get();

    return -1;
}

}