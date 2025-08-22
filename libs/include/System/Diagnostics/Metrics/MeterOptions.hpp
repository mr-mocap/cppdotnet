#include <string>
#include <string_view>


namespace System::Diagnostics::Metrics
{

struct MeterOptions
{
    MeterOptions(std::string_view name) : Name( name ) { }

    std::string Name;
    std::string Version;

    // TODO: Implement Me!
#if 0
    Object Scope;
           Tags;
#endif
};

}
