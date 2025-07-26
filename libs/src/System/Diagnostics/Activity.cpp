#include "System/Diagnostics/Activity.hpp"
#include "System/Diagnostics/ActivitySource.hpp"
#include "System/Convert.hpp"
#include "System/Guid.hpp"
#include "System/Span.hpp"
#include <random>
#include <algorithm>



namespace System::Diagnostics
{

static Activity  DefaultActivity("No Activity");
static Activity *CurrentActivity = nullptr;
EventHandler<ActivityChangedEventArgs> Activity::CurrentChanged;
Func<ActivityTraceId>                  Activity::TraceIdGenerator;


Activity &Activity::Current()
{
    if ( !CurrentActivity )
        return DefaultActivity;
    return *CurrentActivity;
}

void Activity::Current(Activity &new_activity)
{
    ActivityChangedEventArgs data( CurrentActivity, &new_activity );

    CurrentActivity = &new_activity;

    if ( CurrentChanged )
        CurrentChanged( data );
}

std::string_view Activity::ParentId() const
{
    if ( Parent() )
        return Parent()->Id();
    return {};
}

std::string_view Activity::RootId() const
{
    if ( !ParentId().empty() )
        return Parent()->RootId();

    if ( !Id().empty() )
        return Id();

    return {};
}

Activity &Activity::Start()
{
    _parent = CurrentActivity;
    Current( *this );

    // Set the Id
    {
        // First, set IdFormat...
        if ( Parent() )
            _activity_id_format = Parent()->IdFormat();
        else
            _activity_id_format = DefaultIdFormat();

        // Now the Activity Id
        if ( IdFormat() == ActivityIdFormat::W3C )
            _trace_id = (TraceIdGenerator) ? TraceIdGenerator() : ActivityTraceId::CreateRandom();
        else
            _trace_id = ActivityTraceId();

        // NOW set Id
        _id.clear();
        if ( Parent() )
        {
            _id = ParentId();
            _id += '.';
        }
        _id.append( _trace_id.ToHexString() );
    }

    _stopped = false;
    return SetStartTime( DateTime::Now() );
}

void Activity::Stop()
{
    SetEndTime( DateTime::Now() );
    _stopped = true;

    // Change the current activity...
    {
        ActivityChangedEventArgs data( CurrentActivity, _parent );

        CurrentActivity = _parent;
        CurrentChanged( data );
    }
}

Activity &Activity::SetStartTime(DateTime time)
{
    _start_time = time;
    return *this;
}

Activity &Activity::SetEndTime(DateTime time)
{
    _end_time = time;
    return *this;
}

Activity &Activity::SetStatus(ActivityStatusCode code, std::string_view description)
{
    _status = code;
    if ( code == ActivityStatusCode::Error )
        _status_description = description;
    else
        _status_description.clear();

    return *this;
}

TimeSpan Activity::Duration() const
{
    if ( IsStopped() )
        if ( _start_time != DateTime() ) // Check if we actually started!
            return { _end_time - StartTimeUtc() };
    
    return TimeSpan::Zero();
}

const ActivitySource &Activity::Source() const
{
    static ActivitySource dummy("dummy");

    return dummy;
}

Activity &Activity::AddBaggage(std::string_view key, std::string_view value)
{
    _baggage.Add( key, value );
    return *this;
}

Activity &Activity::AddEvent(const ActivityEvent &event)
{
    _activity_events.Add( event );
    return *this;
}

Activity &Activity::AddTag(std::string_view key, std::string_view value)
{
    _tags_to_log.Add( key, value );
    return *this;
}

Activity &Activity::SetBaggage(std::string_view key, std::string_view value)
{
    if ( value.empty() )
    {
        if ( _baggage.ContainsKey( key ) )
            _baggage.Remove( key );
    }
    else
        _baggage[ key ] = value;

    return *this;
}

void Activity::Dispose()
{
    if ( !IsStopped() )
    {
        Stop();
        // TODO: Notify event listeners...
    }
}

void Activity::Dispose(bool disposing)
{
    UNUSED( disposing );

    // NOTE: We should only ever act when disposing is true
}

}