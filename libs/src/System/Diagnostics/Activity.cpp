#include "System/Diagnostics/Activity.hpp"
#include "System/Diagnostics/ActivitySource.hpp"
#include "System/Span.hpp"
#include "System/Convert.hpp"
#include <random>
#include <algorithm>



namespace System::Diagnostics
{

ActivityLink::ActivityLink(const ActivityContext &context)
    :
    _context( context )
{
}

static Activity  DefaultActivity("No Activity");
static Activity *CurrentActivity = nullptr;
EventHandler<ActivityChangedEventArgs> Activity::CurrentChanged;


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

Activity &Activity::Start()
{
    _parent = &Current();
    Current( *this );

    _stopped = false;
    return SetStartTime( DateTime::Now() );
}

void Activity::Stop()
{
    SetEndTime( DateTime::Now() );
    _stopped = true;

    if ( _parent )
        Current( *_parent );
    else
        Current( DefaultActivity );
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

Activity &Activity::AddTag(std::string_view key, std::string_view value)
{
    _tags_to_log.Add( key, value );
    return *this;
}

}