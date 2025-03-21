#include "System/DateTime.hpp"
#include "System/DateOnly.hpp"
#include "System/TimeOnly.hpp"
#include "System/Private/private.hpp"
#include <format>
#include <cmath>

using namespace std::chrono;

namespace System
{

long DateTime::Ticks() const
{
    sys_days time_point_in_days( _date_only );
    sys_days origin( DateOnly::MinValue() );
    sys_days difference = time_point_in_days - origin.time_since_epoch();
    long     calculated_ticks = difference.time_since_epoch().count() * TimeSpan::TicksPerDay();

    //return difference.time_since_epoch().count() / TimeSpan::NanosecondsPerTick();
    return calculated_ticks + _time_only.Ticks();
}

DateTime DateTime::Now()
{
#if 0
    auto local_tp = current_zone()->to_local( system_clock::now() );

    return DateTime( sys_time( local_tp.time_since_epoch() ) );
#else
    system_clock::time_point now = system_clock::now();
    year_month_day ymd{ floor<days>(now) };

    return DateTime( DateOnly( ymd ), TimeOnly( now.time_since_epoch() ) );
#endif
}

DateTime DateTime::UtcNow()
{
    system_clock::time_point now = clock_cast<system_clock, utc_clock>( utc_clock::now() );
    year_month_day ymd{ floor<days>(now) };

    return DateTime( DateOnly( ymd ), TimeOnly( now.time_since_epoch() ) );
}

DateTime DateTime::Today()
{
    year_month_day ymd{ floor<days>( system_clock::now() ) };
    DateTime       td{ DateOnly( ymd ), TimeOnly() };

    POSTCONDITION( td.Hour() == 0 );
    POSTCONDITION( td.Minute() == 0 );
    POSTCONDITION( td.Second() == 0 );

    return td;
}

std::string DateTime::ToString() const
{
    return std::format("{} {}", _date_only.ToString(), _time_only.ToString() );
}
#if 0
DateTime &DateTime::operator +=(std::chrono::system_clock::duration time_duration)
{
    // FIXME
    system_clock::time_point tp( sys_days(_date_only) + system_clock::duration(_time_only.ToTimeSpan()) );

    tp += time_duration;

    {
        sys_days new_time_point_at_start_of_day( floor<days>( tp.time_since_epoch() ) );

        _date_only = DateOnly( new_time_point_at_start_of_day );
        tp -= new_time_point_at_start_of_day.time_since_epoch(); // Subtract off the days so we will be left with the leftover day
    }

    _time_only = TimeOnly::FromTimeSpan( TimeSpan( tp.time_since_epoch() ) );
    return *this;
}

DateTime &DateTime::operator -=(std::chrono::system_clock::duration time_duration)
{
    // FIXME
    system_clock::time_point tp( sys_days(_date_only) + system_clock::duration(_time_only.ToTimeSpan()) );

    tp -= time_duration;

    {
        sys_days new_time_point_at_start_of_day( floor<days>( tp.time_since_epoch() ) );

        _date_only = DateOnly( new_time_point_at_start_of_day );
        tp -= new_time_point_at_start_of_day.time_since_epoch(); // Subtract off the days so we will be left with the leftover day
    }

    _time_only = TimeOnly::FromTimeSpan( TimeSpan( tp.time_since_epoch() ) );
    return *this;
}
#endif

DateTime &DateTime::_accumulate(std::chrono::system_clock::duration time_duration)
{
    // First do the DateOnly part...
    {
        DateOnly result( _date_only );

        {
            days d = floor<days>( time_duration );

            result = result.AddDays( d.count() );
            time_duration -= d;
        }
        {
            months m = floor<months>( time_duration );

            result = result.AddMonths( m.count() );
            time_duration -= m;
        }
        {
            years y = floor<years>( time_duration );

            result = result.AddYears( y.count() );
            time_duration -= y;
        }
        _date_only = result;
    }

    // Then do the TimeOnly part
    {
        int excess_days;

        _time_only = _time_only.Add( time_duration, excess_days );
        _date_only = _date_only.AddDays( excess_days );
    }
    return *this;
}

DateTime DateTime::AddYears(int y) const
{
    return DateTime( _date_only.AddYears(y), _time_only );
}

DateTime DateTime::AddMonths(int months) const
{
    using namespace std::literals;

    // First check that the parameter is within allowed bounds
    if ( months < -120'000 )
        ThrowWithTarget( ArgumentOutOfRangeException("months"sv, "Parameter is less than minimum allowed value"sv) );
    if ( months > 120'000 )
        ThrowWithTarget( ArgumentOutOfRangeException("months"sv, "Parameter is greater than minimum allowed value"sv) );

    return DateTime( _date_only.AddMonths( months ), _time_only );
}

DateTime DateTime::AddDays(double d) const
{
    double ipart;
    double fraction = std::modf( d, &ipart );
    TimeSpan ts_whole_days{ days{ static_cast<int>(ipart) } };
    double   leftover_ticks = fraction * static_cast<double>(TimeSpan::TicksPerDay());
    long fractional_day_in_ticks = static_cast<long>(leftover_ticks);

    return Add( ts_whole_days ).Add( TimeSpan( fractional_day_in_ticks ) );
}

DateTime DateTime::AddHours(double h) const
{
    double ipart;
    double fraction = std::modf( h, &ipart );
    TimeSpan ts_whole_hours{ hours{ static_cast<int>(ipart) } };
    long fractional_hours_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerHour());

    return Add( ts_whole_hours ).Add( TimeSpan( fractional_hours_in_ticks ) );
}

DateTime DateTime::AddMinutes(double m) const
{
    double ipart;
    double fraction = std::modf( m, &ipart );
    TimeSpan ts_whole_minutes{ minutes{ static_cast<int>(ipart) } };
    long fractional_minutes_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerMinute());

    return Add( ts_whole_minutes ).Add( TimeSpan( fractional_minutes_in_ticks ) );
}

DateTime DateTime::AddSeconds(double s) const
{
    double ipart;
    double fraction = std::modf( s, &ipart );
    TimeSpan ts_whole_seconds{ seconds{ static_cast<int>(ipart) } };
    long fractional_seconds_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerSecond());

    return Add( ts_whole_seconds ).Add( TimeSpan( fractional_seconds_in_ticks ) );
}

DateTime DateTime::AddMilliseconds(double ms) const
{
    double ipart;
    double fraction = std::modf( ms, &ipart );
    TimeSpan ts_whole_milliseconds{ milliseconds{ static_cast<int>(ipart) } };
    long fractional_milliseconds_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerMillisecond());

    return Add( ts_whole_milliseconds ).Add( TimeSpan( fractional_milliseconds_in_ticks ) );
}

DateTime DateTime::AddMicroseconds(double micro_seconds) const
{
    double ipart;
    double fraction = std::modf( micro_seconds, &ipart );
    TimeSpan ts_whole_microseconds{ microseconds{ static_cast<int>(ipart) } };
    long fractional_microseconds_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerMicrosecond());

    return Add( ts_whole_microseconds ).Add( TimeSpan( fractional_microseconds_in_ticks ) );
}

DateTime DateTime::AddTicks(long ticks) const
{
    return Add( TimeSpan(ticks) );
}

DateTime DateTime::Add(const TimeSpan &time_span) const
{
    using namespace std::literals;

#if 0
    // Detect a potential wrap-around...
    if ( Ticks() >= 0 )
    {
        if ( MaxValue().Ticks() - Ticks() < time_span.Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is greater than DateTime::MaxValue"sv) );
    }
    else
    {
        if ( time_span.Ticks() < MinValue().Ticks() - Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is less than DateTime::MinValue"sv) );
        
    }

    return *this + time_span;
#else
    // Detect a potential wrap-around...
    if ( Ticks() >= 0 )
    {
        // Overflow a long...
        if ( MaxValue().Ticks() - Ticks() < time_span.Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is greater than DateTime::MaxValue"sv) );
    }
    else
    {
        if ( time_span.Ticks() < MinValue().Ticks() - Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is less than DateTime::MinValue"sv) );
        
    }
        
    // We won't overflow the long, but we still might go out-of-bounds for a DateTime...
    DateTime result( *this );

    result._accumulate( time_span );
    if ( result < MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is less than DateTime::MinValue"sv) );
    else
    {
        if ( result > MaxValue() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is greater than DateTime::MaxValue"sv) );
    }

    return result;
#endif
}

int DateTime::Compare(const DateTime &t1, const DateTime &t2)
{
    auto result{ t1 <=> t2 };

    if ( result == std::strong_ordering::less )
        return -1;
    else if ( result == std::strong_ordering::equal )
        return 0;
    else
        return 1;
}

DateTime DateTime::UnixEpoch()
{
    year_month_day ymd{ floor<days>( system_clock::time_point() ) };

    return DateTime( DateOnly( ymd ), TimeOnly::MinValue() );
}

}