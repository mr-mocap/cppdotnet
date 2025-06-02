#include "System/IO/StringWriter.hpp"


namespace System::IO
{

StringWriter::StringWriter()
{
}

StringWriter::~StringWriter()
{
}

void StringWriter::Write(char value)
{
    _builder.Append( value );
}

void StringWriter::Write(std::string_view message)
{
    _builder.Append( message );
}

}