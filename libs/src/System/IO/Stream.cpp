#include "System/IO/Stream.hpp"
#include "System/IO/IOException.hpp"


namespace System::IO
{

Stream::Stream(std::unique_ptr<std::iostream> &&stream, bool can_read, bool can_write, bool can_seek)
    :
    _stream{ std::move(stream) },
    _canRead{ can_read },
    _canWrite{ can_write },
    _canSeek{ can_seek }
{
}

void Stream::Close()
{
    _close();
}

void Stream::Flush()
{
    _flush();
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

size_t Stream::Length()
{
    return _length();
}

size_t Stream::Position()
{
    // Factor out the most common behavior
    using namespace std::literals;

    if ( !CanSeek() )
    {
        ThrowWithTarget( NotSupportedException("Finding the Position is not supported (Unable to Seek for this stream type)"sv) );
    }

    if ( _stream->fail() )
    {
        ThrowWithTarget( IO::IOException("Stream is in a fail state"sv) );
    }
    return _position(); // Now, call the virtual method
}

void Stream::_close()
{
}

void Stream::_flush()
{
    if ( _stream )
        _stream->flush();
}

size_t Stream::_length()
{
    using namespace std::literals;

    // Default behavior: Throw an exception
    ThrowWithTarget( NotSupportedException("Finding the Length is not supported"sv) );

    return 0;
}

size_t Stream::_position()
{
    return 0;
}

}