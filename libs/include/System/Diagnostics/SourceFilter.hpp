#pragma once

#include "System/Diagnostics/TraceFilter.hpp"
#include <string>


namespace System::Diagnostics
{

class SourceFilter : public TraceFilter
{
public:
    SourceFilter() = delete;
    SourceFilter(const std::string_view source) : _source( source ) { }

    const std::string &Source() const { return _source; }
          void         Source(const std::string_view new_source) { _source = new_source; }

    bool ShouldTrace(const TraceEventCache &cache,
                     const std::string_view source,
                     TraceEventType eventType,
                     int   id,
                     const std::string_view formatOrMessage) override;
protected:
    std::string _source;
};

}