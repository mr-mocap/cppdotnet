#include "System/IO/MemoryStream.hpp"
#include <sstream>
#include <span>


namespace System::IO
{

inline std::stringstream *AsSStream(std::iostream *input)
{
    return static_cast<std::stringstream *>(input);
}

MemoryStream::MemoryStream()
    :
    Stream( std::make_unique<std::stringstream>(), true, true, true )
{
}

std::string MemoryStream::ToArray() const
{
    return AsSStream( _stream.get() )->str();
}

size_t MemoryStream::_length()
{
    return AsSStream( _stream.get() )->str().size();
}

size_t MemoryStream::_position()
{
    return _length();
}

}