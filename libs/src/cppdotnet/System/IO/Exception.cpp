#include <cppdotnet/System/IO/Exception.hpp>


namespace System::IO
{


std::string_view IOException::ClassName() const
{
    return "IOException";
}

std::string_view DirectoryNotFoundException::ClassName() const
{
    return "DirectoryNotFoundException";
}

std::string_view EndOfStreamException::ClassName() const
{
    return "EndOfStreamException";
}

std::string_view FileNotFoundException::ClassName() const
{
    return "FileNotFoundException";
}

std::string_view PathTooLongException::ClassName() const
{
    return "PathTooLongException";
}

}