#include "System/IO/MemoryStream.hpp"
#include "System/Exception.hpp"
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
    using namespace std::literals;

    if ( index < 0 )
        ThrowWithTarget( ArgumentOutOfRangeException("index"sv, "Value is less than 0"sv) );
    if ( count < 0 )
        ThrowWithTarget( ArgumentOutOfRangeException("count"sv, "Value is less than 0"sv) );

    std::size_t s_count = static_cast<std::size_t>(count);
    std::size_t s_index = static_cast<std::size_t>(index);

    if ( (initial_buffer.size() - s_index) < s_count )
        ThrowWithTarget( ArgumentException("initial_buffer size minus index is less than count"sv) );
    
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