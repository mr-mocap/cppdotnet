#include "System/Diagnostics/Debugger.hpp"
#include "System/Private/private.hpp"


namespace System::Diagnostics
{

void Debugger::Log(int level, std::string_view category, std::string_view message)
{
    // assert(category.size() <= 256);

    UNUSED(level);
    UNUSED(category);
    UNUSED(message);

    // TODO: FIXME (in C++23?)
}

}
