#include "System/DateTime.hpp"
#include "System/Private/private.hpp"
#include <format>
#include <cmath>

using namespace std::chrono;

namespace System
{

DateTime::DateTime(int y, int m, int d, int h, int min, int s, int ms)
    :
    _point_in_time( sys_days( year_month_day( year(y) / month(m) / day(d) ) ) )
{
    _point_in_time += hours(h);
    _point_in_time += minutes(min);
    _point_in_time += seconds(s);
    _point_in_time += milliseconds(ms);
}

DateTime DateTime::Date() const
{
    DateTime td( floor<days>( _point_in_time ) );

    POSTCONDITION( td.Hour() == 0 );
    POSTCONDITION( td.Minute() == 0 );
    POSTCONDITION( td.Second() == 0 );

    return td;
}

TimeSpan DateTime::TimeOfDay() const
{
    auto midnight_tp = floor<days>( _point_in_time );

    return TimeSpan( _point_in_time - midnight_tp );
}

int DateTime::Year() const
{
    year_month_day ymd{ floor<days>( _point_in_time ) };
    int year_as_int{ ymd.year() };

    POSTCONDITION( year_as_int >= 1 );
    POSTCONDITION( year_as_int <= 9999 );

    return year_as_int;
}

int DateTime::Month() const
{
    year_month_day ymd{ floor<days>( _point_in_time ) };
    unsigned int month_as_unsigned_int{ ymd.month() };

    POSTCONDITION( month_as_unsigned_int >= 1 );
    POSTCONDITION( month_as_unsigned_int <= 12 );

    return static_cast<int>(month_as_unsigned_int);
}

int DateTime::Day() const
{
    year_month_day ymd{ floor<days>( _point_in_time ) };
    unsigned int day_as_unsigned_int{ ymd.day() };

    POSTCONDITION( day_as_unsigned_int >= 1 );
    POSTCONDITION( day_as_unsigned_int <= 31 );

    return static_cast<int>(day_as_unsigned_int);
}

int DateTime::Hour() const
{
    system_clock::duration tp = _point_in_time.time_since_epoch();
    days d = duration_cast<days>(tp);

    tp -= d;
    auto h = duration_cast<hours>(tp);

    POSTCONDITION( h.count() >= 0 );
    POSTCONDITION( h.count() <= 23 );

    return static_cast<int>( h.count() );
}

int DateTime::Minute() const
{
    auto tp = _point_in_time.time_since_epoch();
    days d = duration_cast<days>(tp);

    tp -= d;
    auto h = duration_cast<hours>(tp);

    tp -= h;
    auto m = duration_cast<minutes>(tp);

    POSTCONDITION( m.count() >= 0 );
    POSTCONDITION( m.count() <= 59 );

    return static_cast<int>( m.count() );
}

int DateTime::Second() const
{
    auto tp = _point_in_time.time_since_epoch();
    days d = duration_cast<days>(tp);

    tp -= d;
    auto h = duration_cast<hours>(tp);

    tp -= h;
    auto m = duration_cast<minutes>(tp);

    tp -= m;
    auto s = duration_cast<seconds>(tp);

    POSTCONDITION( s.count() >= 0 );
    POSTCONDITION( s.count() <= 59 );

    return static_cast<int>( s.count() );
}

int DateTime::Millisecond() const
{
    auto tp = _point_in_time.time_since_epoch();
    days d = duration_cast<days>(tp);

    tp -= d;
    auto h = duration_cast<hours>(tp);

    tp -= h;
    auto m = duration_cast<minutes>(tp);

    tp -= m;
    auto s = duration_cast<seconds>(tp);

    tp -= s;
    auto ms = duration_cast<milliseconds>(tp);

    POSTCONDITION( ms.count() >= 0 );
    POSTCONDITION( ms.count() <= 999 );

    return static_cast<int>( ms.count() );
}

int DateTime::Microsecond() const
{
    auto tp = _point_in_time.time_since_epoch();
    days d = duration_cast<days>(tp);

    tp -= d;
    auto h = duration_cast<hours>(tp);

    tp -= h;
    auto m = duration_cast<minutes>(tp);

    tp -= m;
    auto s = duration_cast<seconds>(tp);

    tp -= s;
    auto ms = duration_cast<milliseconds>(tp);

    tp -= ms;
    auto micro = duration_cast<microseconds>(tp);

    POSTCONDITION( micro.count() >= 0 );
    POSTCONDITION( micro.count() <= 999 );

    return static_cast<int>( micro.count() );
}

int DateTime::Nanosecond() const
{
    auto tp = _point_in_time.time_since_epoch();
    days d = duration_cast<days>(tp);

    tp -= d;
    auto h = duration_cast<hours>(tp);

    tp -= h;
    auto m = duration_cast<minutes>(tp);

    tp -= m;
    auto s = duration_cast<seconds>(tp);

    tp -= s;
    auto ms = duration_cast<milliseconds>(tp);

    tp -= ms;
    auto micro = duration_cast<microseconds>(tp);

    tp -= micro;
    auto nano = duration_cast<nanoseconds>(tp);

    // nano should be in increments of 100 real nanoseconds

    POSTCONDITION( nano.count() >= 0 );
    POSTCONDITION( nano.count() <= 900 );

    return static_cast<int>( micro.count() );
}

long DateTime::Ticks() const
{
    return _point_in_time.time_since_epoch().count() / TimeSpan::NanosecondsPerTick();
}

enum DayOfWeek DateTime::DayOfWeek() const
{
    auto dp = floor<days>(_point_in_time);
    year_month_day ymd{ dp };
    weekday wd{ sys_days( ymd ) };

    return static_cast<enum DayOfWeek>( wd.c_encoding() );
}

int DateTime::DayOfYear() const
{
    auto current_year = floor<years>(_point_in_time);
    auto d = duration_cast<days>(_point_in_time - current_year);

    // Let's add 1 since the subtraction puts us at a 0-based number
    return static_cast<int>( d.count()  + 1 );
}

DateTime DateTime::Now()
{
    auto local_tp = current_zone()->to_local( system_clock::now() );

    return DateTime( sys_time( local_tp.time_since_epoch() ) );
}

DateTime DateTime::UtcNow()
{
    return DateTime( clock_cast<system_clock, utc_clock>( utc_clock::now() ) );
}

DateTime DateTime::Today()
{
    auto tp = floor<days>( system_clock::now() );
    DateTime td( tp );

    POSTCONDITION( td.Hour() == 0 );
    POSTCONDITION( td.Minute() == 0 );
    POSTCONDITION( td.Second() == 0 );

    return td;
}

std::string DateTime::ToString() const
{
    return std::format("{}", _point_in_time);
}

DateTime DateTime::AddYears(int years_to_add) const
{
    TimeSpan ts{ std::chrono::years(years_to_add) };
    DateTime new_value( *this );

    return new_value.Add( ts );
}

DateTime DateTime::AddMonths(int months) const
{
    using namespace std::literals;

    // First check that the parameter is within allowed bounds
    if ( months < -120'000 )
        ThrowWithTarget( ArgumentOutOfRangeException("months"sv, "Parameter is less than minimum allowed value"sv) );
    if ( months > 120'000 )
        ThrowWithTarget( ArgumentOutOfRangeException("months"sv, "Parameter is greater than minimum allowed value"sv) );

    TimeSpan ts{ std::chrono::months(months) };
    DateTime new_value( *this );

    return new_value.Add( ts );
}

DateTime DateTime::AddDays(double d) const
{
    double ipart;
    double fraction = std::modf( d, &ipart );
    TimeSpan ts{ days{ static_cast<int>(ipart) } };
    DateTime new_value( *this );

    return new_value.Add( ts );
}

DateTime DateTime::AddHours(double h) const
{
    return UnixEpoch();
}

DateTime DateTime::AddMinutes(double m) const
{
    return UnixEpoch();
}

DateTime DateTime::AddSeconds(double s) const
{
    return UnixEpoch();
}

DateTime DateTime::AddMilliseconds(double ms) const
{
    return UnixEpoch();
}

DateTime DateTime::AddMicroseconds(double micro_seconds) const
{
    return UnixEpoch();
}

DateTime DateTime::AddTicks(long ticks) const
{
    return UnixEpoch();
}

DateTime DateTime::Add(TimeSpan time_span) const
{
    using namespace std::literals;

    // Detect a potential wrap-around...
    if ( Ticks() >= 0 )
    {
        //if ( MaxValue().Ticks() - Ticks() < std::chrono::system_clock::duration(time_span).count() )
        if ( MaxValue().Ticks() - Ticks() < time_span.Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is greater than DateTime::MinValue"sv) );
    }
    else
    {
        //if ( std::chrono::system_clock::duration(time_span).count() < MinValue().Ticks() - Ticks() )
        if ( time_span.Ticks() < MinValue().Ticks() - Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is less than DateTime::MinValue"sv) );
        
    }

    return DateTime( *this ) += time_span;
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

}