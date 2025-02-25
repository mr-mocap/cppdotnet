#include "System/Diagnostics/Debugger.hpp"
#include "System/Private/private.hpp"


namespace System::Diagnostics
{

#if 0
void Debugger::Log(int level, const std::string &category, const std::string &message)
{
    // assert(category.size() <= 256);
}
#else
void Debugger::Log(const std::string_view message)
{
    UNUSED(message);
    // TODO: Implement me
}
#endif

}
