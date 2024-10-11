#include "System/IO/StreamReader.hpp"
#include "System/IO/FileStream.hpp"


namespace System::IO
{

StreamReader::StreamReader()
{
}

StreamReader::StreamReader(const std::string_view filename)
    :
    _stream{ std::make_unique<FileStream>( filename ) }
{
}

StreamReader::StreamReader(std::unique_ptr<Stream> &&stream)
    :
    _stream{ std::move(stream) }
{
}

StreamReader::~StreamReader()
{
}

void StreamReader::Close()
{
    if ( _stream )
        _stream->Close();
}

int StreamReader::Read()
{
    if ( _stream )
        return _stream->ReadByte();
    return -1;
}

std::string StreamReader::ReadLine()
{
    std::string input_buffer;

    if ( _stream )
    {
        while ( true )
        {
            int character = _stream->ReadByte();

            if ( character == -1 )
                break;
            if ( character == '\n' )
                break;
            input_buffer.push_back( static_cast<std::string::value_type>(character) );
        }
    }
    return input_buffer;
}

}