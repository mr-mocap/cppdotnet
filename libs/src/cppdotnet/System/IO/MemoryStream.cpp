#include <cppdotnet/System/IO/MemoryStream.hpp>
#include <cppdotnet/System/Exception.hpp>
#include <sstream>
#include <algorithm>


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

MemoryStream::MemoryStream(std::string_view initial_buffer)
    :
    // TODO: Remove the creation of a temporary string here in C++26
    Stream( std::make_unique<std::stringstream>( std::string{initial_buffer} ), true, true, true ),
    _initial_capacity{ initial_buffer.size() },
    _capacity{ _initial_capacity }
{
}

MemoryStream::MemoryStream(const std::string &initial_buffer)
    :
    Stream( std::make_unique<std::stringstream>( initial_buffer ), true, true, true ),
    _initial_capacity{ initial_buffer.size() },
    _capacity{ _initial_capacity }
{
}

MemoryStream::MemoryStream(const std::string &initial_buffer, int index, int count, bool writable)
    :
    Stream( std::make_unique<std::stringstream>( initial_buffer.substr(index, count) ), true, writable, true )
{
    if ( index < 0 )
        ThrowWithTarget( ArgumentOutOfRangeException("index", "Value is less than 0") );
    if ( count < 0 )
        ThrowWithTarget( ArgumentOutOfRangeException("count", "Value is less than 0") );

    std::size_t s_count = static_cast<std::size_t>(count);
    std::size_t s_index = static_cast<std::size_t>(index);

    if ( (initial_buffer.size() - s_index) < s_count )
        ThrowWithTarget( ArgumentException("initial_buffer size minus index is less than count") );
    
    _initial_capacity = std::min(s_count, s_index);
    _capacity = _initial_capacity;
}

MemoryStream::~MemoryStream()
{
    _capacity = 0;
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