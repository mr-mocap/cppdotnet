#include "System/TimeSpan.hpp"
#include "System/Exception.hpp"
#include "System/Private/private.hpp"
#include <cmath>

using namespace std::chrono;

namespace System
{

TimeSpan::TimeSpan(int d, int h, int m, int s)
    :
    _time_span( days(d) + hours(h) + minutes(m) + seconds(s) )
{
}

TimeSpan::TimeSpan(int d, int h, int m, int s, int ms)
    :
    _time_span( days(d) + hours(h) + minutes(m) + seconds(s) + milliseconds(ms) )
{
}

int TimeSpan::Days() const
{
    bool negative = (_time_span.count() < 0);
    long d = (negative) ? ceil<days>( _time_span ).count() : floor<days>( _time_span ).count();

    return static_cast<int>(d);
}

int TimeSpan::Hours() const
{
    bool negative = (_time_span.count() < 0);
    long h = (negative) ? ceil<hours>( _time_span ).count() : floor<hours>( _time_span ).count();
    std::ldiv_t  d = std::div( h, static_cast<long>(HoursPerDay()) );

    POSTCONDITION( d.rem >= -23 );
    POSTCONDITION( d.rem <=  23 );

    return d.rem;
}

int TimeSpan::Minutes() const
{
    bool negative = (_time_span.count() < 0);
    long m = (negative) ? ceil<minutes>( _time_span ).count() : floor<minutes>( _time_span ).count();
    std::ldiv_t d = std::div( m, MinutesPerHour() );

    POSTCONDITION( d.rem >= -59 );
    POSTCONDITION( d.rem <=  59 );

    return d.rem;
}

int TimeSpan::Seconds() const
{
    bool negative = (_time_span.count() < 0);
    long s = (negative) ? ceil<seconds>( _time_span ).count() : floor<seconds>( _time_span ).count();
    std::ldiv_t d = std::div( s, SecondsPerMinute() );

    POSTCONDITION( d.rem >= -59 );
    POSTCONDITION( d.rem <=  59 );

    return d.rem;
}

int TimeSpan::Milliseconds() const
{
    bool negative = (_time_span.count() < 0);
    long ms = (negative) ? ceil<milliseconds>( _time_span ).count() : floor<milliseconds>( _time_span ).count();
    std::ldiv_t d = std::div( ms, MillisecondsPerSecond() );

    POSTCONDITION( d.rem >= -999 );
    POSTCONDITION( d.rem <=  999 );

    return d.rem;
}

int TimeSpan::Microseconds() const
{
    bool negative = (_time_span.count() < 0);
    long ms = (negative) ? ceil<microseconds>( _time_span ).count() : floor<microseconds>( _time_span ).count();
    std::ldiv_t d = std::div( ms, MicrosecondsPerSecond() );

    POSTCONDITION( d.rem >= -999'999 );
    POSTCONDITION( d.rem <=  999'999 );

    return d.rem;
}

int TimeSpan::Nanoseconds() const
{
    // System clock is typically in nanoseconds, so we can just use the count() directly
    long ns = _time_span.count();
    std::ldiv_t d = std::div( ns, NanosecondsPerSecond() );

    POSTCONDITION( d.rem >= -99'999'999 );
    POSTCONDITION( d.rem <=  99'999'999 );

    return d.rem;
}

double TimeSpan::TotalDays() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerDay() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerDay() );

    return int_part + frac_part;
}

double TimeSpan::TotalHours() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerHour() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerHour() );

    return int_part + frac_part;
}

double TimeSpan::TotalMinutes() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerMinute() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerMinute() );

    return int_part + frac_part;
}

double TimeSpan::TotalSeconds() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerSecond() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerSecond() );

    return int_part + frac_part;
}

double TimeSpan::TotalMilliseconds() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerMillisecond() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerMillisecond() );

    return int_part + frac_part;
}

double TimeSpan::TotalMicroseconds() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerMicrosecond() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerMicrosecond() );

    return int_part + frac_part;
}

double TimeSpan::TotalNanoseconds() const
{
    return _time_span.count();
}

TimeSpan TimeSpan::Add(const TimeSpan &time_span) const
{
    using namespace std::literals;

    // Detect a potential wrap-around...
    if ( Ticks() >= 0 )
    {
        if ( MaxValue().Ticks() - Ticks() < time_span.Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting TimeSpan is greater than TimeSpan::MaxValue"sv) );
    }
    else
    {
        if ( time_span.Ticks() < MinValue().Ticks() - Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is less than DateTime::MinValue"sv) );
        
    }
    return *this + time_span;
}

TimeSpan TimeSpan::Subtract(const TimeSpan &time_span) const
{
    using namespace std::literals;

    // Detect a potential wrap-around...
    if ( Ticks() >= 0 )
    {
        if ( MinValue().Ticks() + Ticks() < time_span.Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is less than DateTime::MinValue"sv) );
    }
    else
    {
        if ( time_span.Ticks() < MaxValue().Ticks() - Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting TimeSpan is greater than TimeSpan::MaxValue"sv) );
        
    }
    return *this - time_span;
}

TimeSpan TimeSpan::Multiply(double scalar) const
{
#if 0
    using namespace std::literals;

    // Detect a potential wrap-around...
    long long this_count = _time_span.count();
    long long other_count = time_span._time_span.count();
    long long new_value = this_count * other_count;

    if ( new_value > system_clock::duration( MaxValue() ).count() )
        ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting TimeSpan is greater than TimeSpan::MaxValue"sv) );
    else
    {
        if ( new_value < system_clock::duration( MinValue() ).count() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is less than DateTime::MinValue"sv) );
    }
#endif
    // TODO: Implement Me Properly!
    return *this * scalar;
}

TimeSpan TimeSpan::Divide(double scalar) const
{
    // TODO: Implement Me Properly!
    return *this / scalar;
}

std::string TimeSpan::ToString() const
{
    return std::format("{}", _time_span);
}

}