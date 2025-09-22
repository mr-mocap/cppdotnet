#pragma once

#include <cppdotnet/System/Diagnostics/Metrics/Meter.hpp>
#include <vector>


namespace System::Diagnostics::Metrics
{

class IMeterFactory
{
public:
    IMeterFactory() = default;
    virtual ~IMeterFactory() = default;

    virtual Meter Create(const MeterOptions &options);

    void Dispose();
protected:
    std::vector<Meter> _cached_meters;
};

}