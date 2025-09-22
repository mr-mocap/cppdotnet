#pragma once

#include <cppdotnet/System/Diagnostics/Tracing/DiagnosticCounter.hpp>
#include <cppdotnet/System/Func.hpp>

namespace System::Diagnostics::Tracing
{

class PollingCounter : public DiagnosticCounter
{
public:
    PollingCounter(const std::string_view name, EventSource &event_source, Func<double> metric_provider)
        :
        DiagnosticCounter(name, event_source)
    {
    }

};

}