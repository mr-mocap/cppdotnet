#include "System/IO/IOException.hpp"


namespace System::IO
{


std::string_view IOException::ClassName() const
{
    using namespace std::literals;

    return "IOException"sv;
}

}