#include "System/Diagnostics/TraceFilter.hpp"
#include "System/Diagnostics/SourceLevels.hpp"
#include "System/Diagnostics/TraceEventCache.hpp"


namespace System::Diagnostics
{

class EventTypeFilter : public TraceFilter
{
public:
    EventTypeFilter() = delete;
    EventTypeFilter(SourceLevels level) : _level( level ) { }
   ~EventTypeFilter() = default;

    SourceLevels EventType() const { return _level; }
            void EventType(SourceLevels new_level) { _level = new_level; }

    bool ShouldTrace(const TraceEventCache &cache,
                           std::string_view source,
                             TraceEventType eventType,
                                        int id,
                           std::string_view formatOrMessage) override;
protected:
    SourceLevels _level;

    friend bool operator ==(const EventTypeFilter &left, const EventTypeFilter &right)
    {
        return left.EventType() == right.EventType();
    }
};

}