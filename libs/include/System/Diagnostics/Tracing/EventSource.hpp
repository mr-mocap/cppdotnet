#include "System/Diagnostics/Tracing/EventSourceSettings.hpp"
#include <string>
#include <string_view>

namespace System::Diagnostics::Tracing
{

class EventSource
{
public:
    EventSource() : EventSource(false) { }

    EventSource(bool throw_exception_on_error)
        :
        _settings( throw_exception_on_error ? EventSourceSettings::ThrowOnEventWriteErrors : EventSourceSettings::Default )
    {
    }

    EventSource(const std::string_view name)
        :
        _name( name )
    {
    }

    EventSource(EventSourceSettings settings)
        :
        _settings( settings )
    {
    }

    EventSource(const std::string_view event_source_name, EventSourceSettings settings)
        :
        _name( event_source_name ),
        _settings( settings )
    {
    }

    std::string_view Name() const { return _name; }

    const EventSourceSettings &Settings() const { return _settings; }

    void Write(std::string_view event_name);
protected:
    std::string         _name;
    EventSourceSettings _settings = EventSourceSettings::Default;
};

}