#pragma once


#include "System/Diagnostics/Metrics/MeterOptions.hpp"


namespace System::Diagnostics::Metrics
{

class Meter
{
public:
    Meter(const std::string_view name)
        :
        _name{ name }
    {
    }
    Meter(const std::string_view name, const std::string_view version)
        :
        _name{ name },
        _version{ version }
    {
    }
    Meter(const MeterOptions &options)
        :
        _name{ options.Name },
        _version{ options.Version }
    {
    }

    const std::string_view Name() const { return _name; }
    const std::string_view Version() const { return _version; }

protected:
    std::string _name;
    std::string _version;

    // TODO: Implement Scope, Tags
};

}
