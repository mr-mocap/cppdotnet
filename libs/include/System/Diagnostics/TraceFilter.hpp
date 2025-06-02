#pragma once

#include "System/Diagnostics/TraceEventType.hpp"
#include "System/Private/private.hpp"
#include <string_view>
#include <format>


namespace System::Diagnostics
{

class TraceEventCache;

class TraceFilter
{
public:
    TraceFilter() = default;
    virtual ~TraceFilter() = default;

    virtual bool ShouldTrace(const TraceEventCache &cache,
                             std::string_view source,
                             TraceEventType eventType,
                             int   id,
                             std::string_view formatOrMessage)
    {
        UNUSED(cache);
        UNUSED(source);
        UNUSED(eventType);
        UNUSED(id);
        UNUSED(formatOrMessage);

        return false;
    }
    
    virtual std::string ToString() const { return std::format("{}", "System::Diagnostics::TraceFilter IMPLEMENT ME!"); }
};

}