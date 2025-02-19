#pragma once

#include "System/Diagnostics/SourceLevels.hpp"
#include <string>
#include <string_view>


namespace System
{

class TraceSource
{
public:
    TraceSource(const std::string_view name) : _name{ name } { }
    TraceSource(const std::string_view name, Diagnostics::SourceLevel default_level) : _name{ name }, _level{ default_level } { }

    Diagnostics::SourceLevel DefaultLevel() const { return _level; }

    const std::string &Name() const { return _name; }
protected:
    std::string _name;
    Diagnostics::SourceLevel _level{ Diagnostics::SourceLevel::Off };
};

}