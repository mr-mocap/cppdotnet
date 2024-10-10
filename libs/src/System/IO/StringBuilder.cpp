#include "System/IO/StringBuilder.hpp"


namespace System::IO
{

StringBuilder &StringBuilder::Append(char value)
{
    _string.push_back( value );
    return *this;
}

StringBuilder &StringBuilder::Append(const std::string_view value)
{
    _string.append( value );
    return *this;
}

StringBuilder &StringBuilder::Append(const std::string &value)
{
    _string.append( value );
    return *this;
}

StringBuilder &StringBuilder::Clear()
{
    _string.clear();
    return *this;
}
}