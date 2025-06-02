#include "System/IO/FileStream.hpp"
#include <fstream>


namespace System::IO
{

static std::ios_base::openmode MapMode(const FileMode mode)
{
    switch ( mode )
    {
    case FileMode::CreateNew:
        return std::ios_base::out | std::ios_base::in | std::ios_base::trunc;

    case FileMode::Create:
        return std::ios_base::out | std::ios_base::in;

    case FileMode::Open:
    case FileMode::OpenOrCreate:
        return std::ios_base::out | std::ios_base::in;

    case FileMode::Truncate:
        return std::ios_base::out | std::ios_base::in | std::ios_base::trunc;

    case FileMode::Append:
        return std::ios_base::in | std::ios_base::out | std::ios_base::app;
    }

    return std::ios_base::out | std::ios_base::in; // Shouldn't happen, but probably a decent default
}

inline std::fstream *AsFStream(std::iostream *input)
{
    return static_cast<std::fstream *>(input);
}

FileStream::FileStream(std::string_view filename)
    :
    Stream( std::make_unique<std::fstream>( std::string{filename} ), true, true, true )
{
}

FileStream::FileStream(std::string_view filename, const FileMode mode)
    :
    Stream( std::make_unique<std::fstream>( std::string{filename}, MapMode(mode) ), true, true, true )
{
}

FileStream::~FileStream()
{
    _stream.reset();
}

void FileStream::_close()
{
    if ( _stream )
    {
        AsFStream( _stream.get() )->close();
    }
}

}