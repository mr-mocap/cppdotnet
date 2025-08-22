#include "System/Diagnostics/SourceLevels.hpp"
#include <string>
#include <string_view>


namespace System::Diagnostics
{

class TraceSource
{
public:
    TraceSource(std::string_view name) : _name{ name } { }
    TraceSource(std::string_view name, Diagnostics::SourceLevels default_level) : _name{ name }, _level{ default_level } { }

    Diagnostics::SourceLevels DefaultLevel() const { return _level; }

    std::string_view Name() const { return _name; }
protected:
    std::string               _name;
    Diagnostics::SourceLevels _level{ Diagnostics::SourceLevels::Off };
};

}