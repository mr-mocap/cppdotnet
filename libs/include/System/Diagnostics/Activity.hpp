#pragma once

#include "System/ReadOnlySpan.hpp"
#include "System/EventArgs.hpp"
#include "System/EventHandler.hpp"
#include "System/DateTime.hpp"
#include "System/Diagnostics/ActivitySource.hpp"
#include <array>
#include <string>
#include <cstddef>
#include <concepts>


namespace System::Diagnostics
{

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

struct ActivityTraceId
{
    ActivityTraceId()
    {
        _id.fill( std::byte(0) );
    }
    ActivityTraceId(const ActivityTraceId &other)
    {
        _id = other._id;
    }

    ActivityTraceId &operator =(const ActivityTraceId &other)
    {
        _id = other._id;
        return *this;
    }

    bool operator ==(const ActivityTraceId &other);

    static ActivityTraceId CreateRandom();

    static ActivityTraceId CreateFromString(ReadOnlySpan<char> input);
    static ActivityTraceId CreateFromBytes(ReadOnlySpan<std::byte> input);

    std::string ToHexString() const;

    std::string ToString() const { return ToHexString(); }
protected:
    std::array<std::byte, 16> _id;

    ActivityTraceId(const std::array<std::byte, 16> &array)
    {
        for (size_t i = 0; i < _id.size(); ++i)
            _id[ i ] = array[i];
    }
};

class ActivitySpanId
{
public:
    ActivitySpanId()
    {
        _id.fill( std::byte(0) );
    }

    ActivitySpanId(const ActivitySpanId &other)
    {
        _id = other._id;
    }

    ActivitySpanId &operator =(const ActivitySpanId &other) = default;

    bool operator ==(const ActivitySpanId &other);

    static ActivitySpanId CreateRandom();

    static ActivitySpanId CreateFromString(ReadOnlySpan<char> input);
    static ActivitySpanId CreateFromBytes(ReadOnlySpan<std::byte> input);

    std::string ToHexString() const;

    std::string ToString() const { return ToHexString(); }
protected:
    std::array<std::byte, 8> _id;

    ActivitySpanId(const std::array<std::byte, 8> &array)
    {
        for (size_t i = 0; i < _id.size(); ++i)
            _id[ i ] = array[i];
    }
};

class ActivityContext
{
public:
    ActivityContext() = default;

    ActivityContext(const ActivityTraceId &trace_id,
                    const ActivitySpanId  &span_id,
                    ActivityTraceFlags     trace_flags,
                    const std::string_view trace_state,
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
    const std::string    &TraceState() const { return _trace_state; }

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
    ActivityEvent(const std::string_view name)
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
    ActivityKind    Kind = ActivityKind::Internal;
    std::string     Name;
#if 0
    T            Parent;
    ActivityTagsCollection SamplingTags;
#endif
    ActivitySource  Source;
    ActivityTraceId TraceId;
    std::string     TraceState;
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

    const DateTime &StartTimeUtc() const { return _start_time; }

    Activity &SetStartTime(DateTime time);
    Activity &SetEndTime(DateTime time);
    Activity &SetStatus(ActivityStatusCode code, std::string_view description = {});

    Activity &Start();
    void      Stop();

    bool IsStopped() const { return _stopped; }

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
    Activity          *_parent = nullptr;
    DateTime           _start_time;
    DateTime           _end_time;
    bool               _stopped = true;
};

}