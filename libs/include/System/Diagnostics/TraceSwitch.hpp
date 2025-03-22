#pragma once

#include "System/Diagnostics/Switch.hpp"
#include "System/Diagnostics/TraceLevel.hpp"


namespace System::Diagnostics
{

class TraceSwitch : public Switch
{
public:
    TraceSwitch(const std::string_view display_name, const std::string_view description)
        :
        Switch( display_name, description )
    {
    }

    TraceSwitch(const std::string_view display_name, const std::string_view description, const std::string_view default_switch_value);
        :
        Switch( display_name, description, default_switch_value )
    {
    }

    TraceLevel Level() const { return _trace_level; }
    void       Level(TraceLevel new_level)
    {
        _trace_level = new_level;
    }

    bool TraceError()   const { return _trace_level >= TraceLevel::Error; }
    bool TraceWarning() const { return _trace_level >= TraceLevel::Warning; }
    bool TraceInfo()    const { return _trace_level >= TraceLevel::Info; }
    bool TraceVerbose() const { return _trace_level >= TraceLevel::Verbose; }
protected:
    TraceLevel _trace_level{ TraceLevel::Off };
};

}