#include <cppdotnet/System/IO/StringReader.hpp>
#include <cppdotnet/System/Environment.hpp>


namespace System::IO
{

StringReader::~StringReader()
{
}

void StringReader::Close()
{
}

int StringReader::Read()
{
    if ( _position < _data.size() )
        return _data[ _position++ ];

    return -1;
}

std::string StringReader::ReadLine()
{
    if ( _position < _data.size() )
    {
        std::string::size_type newline_pos = _data.find( System::Environment::NewLine(), _position );

        if ( newline_pos != std::string::npos )
        {
            std::string line{ _data.substr( _position, newline_pos - _position ) };

            _position = newline_pos + 1;
            return line;
        }
    }
    return {};
}

}