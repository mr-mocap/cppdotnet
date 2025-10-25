#pragma once

#include <cppdotnet/System/ReadOnlySpan.hpp>
#include <cppdotnet/System/EventArgs.hpp>
#include <cppdotnet/System/EventHandler.hpp>
#include <cppdotnet/System/DateTimeOffset.hpp>
#include <cppdotnet/System/Func.hpp>
#include <cppdotnet/System/Diagnostics/ActivityTraceId.hpp>
#include <cppdotnet/System/Diagnostics/ActivitySpanId.hpp>
#include <cppdotnet/System/Private/enum.hpp>
#include <cppdotnet/System/Collections/Generic/List.hpp>
#include <cppdotnet/System/Collections/Generic/ICollection.hpp>
#include <cppdotnet/System/Collections/Specialized/StringDictionary.hpp>
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
                    bool                   is_remote = false)
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


// TODO: Second template parameter of ActivityTagsCollection SHOULD be a base Object instead of a std::string
using ActivityTagsCollection = System::Collections::Specialized::StringDictionary;

class ActivityEvent
{
public:
    ActivityEvent(std::string_view name)
        :
        ActivityEvent( name, System::DateTimeOffset::Now(), ActivityTagsCollection() )
    {
    }
    ActivityEvent(std::string_view name,
                  const System::DateTimeOffset &timestamp,
                  const ActivityTagsCollection &tags)
        :
        _name( name ),
        _timestamp( timestamp ),
        _activity_tags( tags )
    {
    }

    std::string_view Name() const { return _name; }

    const ActivityTagsCollection &Tags() const { return _activity_tags; }

    const System::DateTimeOffset &Timestamp() const { return _timestamp; }
protected:
    std::string _name;
    System::DateTimeOffset _timestamp;
    ActivityTagsCollection _activity_tags;
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

class ActivityLink
{
public:
    ActivityLink(const ActivityContext &context, const ActivityTagsCollection &tags)
        :
        _context( context ),
        _activity_tags( tags )
    {
    }

    const ActivityContext &Context() const { return _context; }

    const ActivityTagsCollection &Tags() const { return _activity_tags; }

    bool operator ==(const ActivityLink &)
    {
        return false; // TODO: FIXME!
    }

    bool operator !=(const ActivityLink &)
    {
        return true; // TODO: FIXME!
    }
protected:
    ActivityContext        _context;
    ActivityTagsCollection _activity_tags;
};

template <class T>
    requires ( std::same_as<T, std::string> || std::same_as<T, ActivityContext> )
struct ActivityCreationOptions
{
    ActivityKind           Kind = ActivityKind::Internal;
    Collections::Generic::List<ActivityLink> Links;
    std::string            Name;
    T                      Parent;
    ActivityTagsCollection SamplingTags;
    ActivitySource        *Source = nullptr;
#if 0
                           Tags;
#endif
    ActivityTraceId        TraceId;
    std::string            TraceState;
};

class Activity
{
public:
    Activity(std::string_view operation_name)
      :
      _operation_name( operation_name )
    {
    }

    Activity(const Activity &) = default;
    Activity(Activity &&) = default;
    Activity &operator =(const Activity &) = default;
    Activity &operator =(Activity &&) = default;

    std::string_view DisplayName() const { return _display_name; }
                void DisplayName(std::string_view dn) { _display_name = dn; }
    
    std::string_view StatusDescription() const { return _status_description; }

    enum ActivityTraceFlags ActivityTraceFlags() const { return _activity_trace_flags; }
                       void ActivityTraceFlags(enum ActivityTraceFlags flags) { _activity_trace_flags = flags; }
    
    enum ActivityKind Kind() const { return _activity_kind; }

    std::string_view Id() const { return _id; }
    std::string_view ParentId() const;
    std::string_view RootId() const;

    const Activity *Parent() const { return _parent; }

    ActivityIdFormat IdFormat() const { return _activity_id_format; }

    ActivityIdFormat DefaultIdFormat() const { return _default_activity_id_format; }
                void DefaultIdFormat(ActivityIdFormat new_value) { _default_activity_id_format = new_value; }

    std::string_view OperationName() const { return _operation_name; }

    TimeSpan Duration() const;

    virtual void Dispose();

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

    Activity &AddEvent(const ActivityEvent &event);

    Activity &AddTag(std::string_view key, std::string_view value);

    Activity &SetBaggage(std::string_view key, std::string_view value);

    const Collections::Specialized::StringDictionary &Baggage() const { return _baggage; }

    const Collections::Specialized::StringDictionary &Tags() const { return _tags_to_log; }

    const Collections::Generic::List<Diagnostics::ActivityEvent> &Events() const { return _activity_events; }

    static EventHandler<ActivityChangedEventArgs> CurrentChanged;

    static Func<ActivityTraceId> TraceIdGenerator;
protected:
    std::string _operation_name;
    std::string _display_name;
    std::string _id;
    enum ActivityKind       _activity_kind        = ActivityKind::Internal;
    enum ActivityTraceFlags _activity_trace_flags = ActivityTraceFlags::None;
    enum ActivityIdFormat   _activity_id_format         = ActivityIdFormat::W3C;
    enum ActivityIdFormat   _default_activity_id_format = ActivityIdFormat::W3C;
    enum ActivityStatusCode _status               = ActivityStatusCode::Unset;
    std::string        _status_description;
    ActivityTraceId    _trace_id;
    ActivityContext    _activity_context;
    Collections::Specialized::StringDictionary _tags_to_log;
    Collections::Specialized::StringDictionary _baggage;
    Collections::Generic::List<Diagnostics::ActivityEvent> _activity_events;
    Activity          *_parent = nullptr;
    DateTime           _start_time;
    DateTime           _end_time;
    bool               _stopped = true;

    virtual void Dispose(bool disposing);
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