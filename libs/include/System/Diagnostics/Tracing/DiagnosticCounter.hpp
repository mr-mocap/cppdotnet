#include "System/Diagnostics/Tracing/EventSource.hpp"
#include <string>

namespace System::Diagnostics::Tracing
{

class DiagnosticCounter
{
public:
    DiagnosticCounter();

    const std::string &Name() const { return _name; }
    const std::string &DisplayName() const { return _display_name; }
    const std::string &DisplayUnits() const { return _display_units; }

    void AddMetadata(const std::string_view key, const std::string_view value);

    //const EventSource &EventSource() const { return _event_source; }
protected:
    std::string _name;
    std::string _display_name;
    std::string _display_units;
    EventSource _event_source;
};

}