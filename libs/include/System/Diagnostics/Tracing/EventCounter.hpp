#include "System/Diagnostics/Tracing/EventSource.hpp"
#include <string>
#include <string_view>


namespace System::Diagnostics::Tracing
{

class EventCounter
{
public:
    EventCounter(std::string_view name, EventSource &event_source)
        :
        _name( name ),
        _event_source( event_source )
    {
    }

    const std::string_view Name() const { return _name; }

    const std::string_view DisplayName() const { return _display_name; }

    const std::string_view DisplayUnits() const { return _display_units; }

    EventSource &EventSource() const { return _event_source; }
protected:
    std::string  _name;
    std::string  _display_name;
    std::string  _display_units;
    EventSource &_event_source;
};

}