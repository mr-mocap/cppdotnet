#include "System/Collections/Generic/KeyNotFoundException.hpp"


namespace System::Collections::Generic
{

std::string_view KeyNotFoundException::ClassName() const
{
    using namespace std::literals;

    return "KeyNotFoundException"sv;
}

}