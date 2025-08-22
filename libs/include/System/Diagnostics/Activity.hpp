#include "System/ReadOnlySpan.hpp"
#include "System/EventArgs.hpp"
#include "System/EventHandler.hpp"
#include "System/DateTime.hpp"
#include "System/Diagnostics/ActivityTraceId.hpp"
#include "System/Diagnostics/ActivitySpanId.hpp"
#include "System/Private/enum.hpp"
#include "System/Collections/Specialized/StringDictionary.hpp"
#include <array>
#include <string>
#include <cstddef>
#include <concepts>
#include <map>
#include <memory>


namespace System::Diagnostics
{

class ActivitySource;

enum class ActivityTraceFlags
{
    None = 0,    ///@< The activity has not been marked
    Recorded = 1 ///@< The activity (or more likely its parents) has been marked as useful to record
};

enum class ActivityStatusCode
{
    Unset = 0,  ///@< Unset status code is the default value indicating the status code is not initialized
    Ok    = 1,  ///@< Status code indicating the operation has been validated and completed successfully
    Error = 2   ///@< Status code indicating an error is encountered during the operation
};

enum class ActivityKind
{
    Internal = 0, ///@< Internal operation within an application, as opposed to operations with remote parents or children. This is the default value.
    Server   = 1, ///@< Requests incoming from external component
    Client   = 2, ///@< Outgoing request to the external component
    Producer = 3, ///@< Output provided to external components
    Consumer = 4  ///@< Output received from an external component
};

enum class ActivityIdFormat
{
    Unknown      = 0,
    Hierarchical = 1,
    W3C          = 2
};


class ActivityContext
{
public:
    ActivityContext() = default;

    ActivityContext(const ActivityTraceId &trace_id,
                    const ActivitySpanId  &span_id,
                    ActivityTraceFlags     trace_flags,
                    std::string_view       trace_state,
                    const bool             is_remote)
        :
        _trace_id( trace_id ),
        _span_id( span_id ),
        _trace_flags( trace_flags ),
        _trace_state( trace_state ),
        _is_remote( is_remote )
    {
    }

    const ActivityTraceId &TraceId() const { return _trace_id; }
    const ActivitySpanId  &SpanId() const  { return _span_id; }

    ActivityTraceFlags    TraceFlags() const { return _trace_flags; }
    std::string_view      TraceState() const { return _trace_state; }

    bool IsRemote() const { return _is_remote; }
protected:
    ActivityTraceId    _trace_id;
    ActivitySpanId     _span_id;
    ActivityTraceFlags _trace_flags;
    std::string        _trace_state;
    bool               _is_remote = false;
};


class ActivityEvent
{
public:
    ActivityEvent(std::string_view name)
        :
        _name( name )
    {
    }

protected:
    std::string _name;
};

class Activity;

class ActivityChangedEventArgs : public EventArgs
{
public:
    ActivityChangedEventArgs(Activity *previous, Activity *current)
        :
        _current( current ),
        _previous( previous )
    {
    }
    using EventArgs::EventArgs;

    Activity &Current() { return *_current; }
    Activity &Previous() { return *_previous; }
protected:
    Activity *_current  = nullptr;
    Activity *_previous = nullptr;
};

template <class T>
    requires ( std::same_as<T, std::string> || std::same_as<T, ActivityContext> )
struct ActivityCreationOptions
{
    ActivityKind     Kind = ActivityKind::Internal;
    std::string      Name;
#if 0
    T            Parent;
    ActivityTagsCollection SamplingTags;
#endif
    ActivitySource  *Source = nullptr;
    ActivityTraceId  TraceId;
    std::string      TraceState;
};

class ActivityLink
{
public:
    ActivityLink(const ActivityContext &context);

    const ActivityContext &Context() const { return _context; }
protected:
    ActivityContext _context;
};

class Activity
{
public:
    Activity(std::string_view operation_name)
      :
      _operation_name( operation_name )
    {
    }
    Activity(const char *operation_name)
      :
      _operation_name( operation_name )
    {
    }

    Activity(const Activity &) = default;
    Activity(Activity &&) = default;
    Activity &operator =(const Activity &) = default;
    Activity &operator =(Activity &&) = default;

    const std::string &DisplayName() const { return _display_name; }
    void DisplayName(std::string_view dn) { _display_name = dn; }
    
    const std::string &StatusDescription() const { return _status_description; }

    enum ActivityTraceFlags ActivityTraceFlags() const { return _activity_trace_flags; }
                       void ActivityTraceFlags(enum ActivityTraceFlags flags) { _activity_trace_flags = flags; }
    
    enum ActivityKind Kind() const { return _activity_kind; }

    const std::string &Id() const { return _id; }

    const std::string &OperationName() const { return _operation_name; }

    TimeSpan Duration() const;

    bool Recorded() const { return _activity_trace_flags == ActivityTraceFlags::Recorded; }

    ActivityStatusCode Status() const { return _status; }

    const ActivityTraceId &TraceId() const { return _trace_id; }
    const ActivityContext &Context() const { return _activity_context; }

    static Activity &Current();
    static void      Current(Activity &new_activity);

    const ActivitySource &Source() const;

    const DateTime &StartTimeUtc() const { return _start_time; }

    Activity &SetStartTime(DateTime time);
    Activity &SetEndTime(DateTime time);
    Activity &SetStatus(ActivityStatusCode code, std::string_view description = {});

    Activity &Start();
    void      Stop();

    bool IsStopped() const { return _stopped; }

    Activity &AddBaggage(std::string_view key, std::string_view value);

    Activity &AddTag(std::string_view key, std::string_view value);

    const System::Collections::Generic::List<std::unique_ptr<System::Diagnostics::ActivityEvent>> &Events() const { return _activity_events; }

    static EventHandler<ActivityChangedEventArgs> CurrentChanged;
protected:
    std::string _operation_name;
    std::string _display_name;
    std::string _id;
    enum ActivityKind  _activity_kind = ActivityKind::Internal;
    enum ActivityTraceFlags _activity_trace_flags = ActivityTraceFlags::None;
    ActivityStatusCode _status = ActivityStatusCode::Unset;
    std::string        _status_description;
    ActivityTraceId    _trace_id;
    ActivityContext    _activity_context;
    System::Collections::Specialized::StringDictionary _tags_to_log;
    System::Collections::Specialized::StringDictionary _baggage;
    System::Collections::Generic::List<std::unique_ptr<System::Diagnostics::ActivityEvent>> _activity_events;
    Activity          *_parent = nullptr;
    DateTime           _start_time;
    DateTime           _end_time;
    bool               _stopped = true;
};

}

namespace System
{

template <>
struct EnumPolicy<Diagnostics::ActivityTraceFlags> : EnumTraitTypes<Diagnostics::ActivityTraceFlags>
{
public:

    static constexpr std::string_view EnumName = "ActivityTraceFlags";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",     Diagnostics::ActivityTraceFlags::None     },
            { "Recorded", Diagnostics::ActivityTraceFlags::Recorded }
        };
};

template <>
struct EnumPolicy<Diagnostics::ActivityStatusCode> : EnumTraitTypes<Diagnostics::ActivityStatusCode>
{
    static constexpr std::string_view EnumName = "ActivityStatusCode";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Unset", Diagnostics::ActivityStatusCode::Unset },
            { "Ok",    Diagnostics::ActivityStatusCode::Ok },
            { "Error", Diagnostics::ActivityStatusCode::Error }
        };
};

template <>
struct EnumPolicy<Diagnostics::ActivityKind> : EnumTraitTypes<Diagnostics::ActivityKind>
{
    static constexpr std::string_view EnumName = "ActivityKind";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Internal", Diagnostics::ActivityKind::Internal },
            { "Server",   Diagnostics::ActivityKind::Server },
            { "Client",   Diagnostics::ActivityKind::Client },
            { "Producer", Diagnostics::ActivityKind::Producer },
            { "Consumer", Diagnostics::ActivityKind::Consumer }
        };
};

template <>
struct EnumPolicy<Diagnostics::ActivityIdFormat> : EnumTraitTypes<Diagnostics::ActivityIdFormat>
{
    static constexpr std::string_view EnumName = "ActivityIdFormat";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Unknown",      Diagnostics::ActivityIdFormat::Unknown },
            { "Hierarchical", Diagnostics::ActivityIdFormat::Hierarchical },
            { "W3C",          Diagnostics::ActivityIdFormat::W3C }
        };
};

}