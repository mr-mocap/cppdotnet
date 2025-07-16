#include "System/IO/StreamWriter.hpp"
#include "System/IO/FileStream.hpp"


namespace System::IO
{

StreamWriter::StreamWriter(std::string_view filename)
    :
    _stream{ std::make_unique<FileStream>( filename ) }
{
}

StreamWriter::~StreamWriter()
{
}

void StreamWriter::Close()
{
    if ( _stream )
        _stream->Close();
}

void StreamWriter::Flush()
{
    if ( _stream )
        _stream->Flush();
}

void StreamWriter::Write(char value)
{
    if ( _stream )
        _stream->WriteByte( static_cast<uint8_t>(value) );
}

void StreamWriter::Write(std::string_view message)
{
    if ( _stream )
        _stream->Write( message );
}

}