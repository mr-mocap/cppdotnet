module;

export module System:TimeSpan;

export import <chrono>;
export import <compare>;
export import <string>;
export import <format>;
import <cstdlib>;
import System:Exception;

namespace System
{

export
class TimeSpan
{
public:
    TimeSpan() { }
   ~TimeSpan() { }
    explicit TimeSpan(int hours, int minutes, int seconds)
        :
        TimeSpan(0, hours, minutes, seconds)
    {
    }
    explicit TimeSpan(int d, int h, int m, int s)
        :
        _time_span( std::chrono::days(d) + std::chrono::hours(h) + std::chrono::minutes(m) + std::chrono::seconds(s) )
    {
    }
    explicit TimeSpan(int d, int h, int m, int s, int ms)
        :
        _time_span( std::chrono::days(d) + std::chrono::hours(h) + std::chrono::minutes(m) + std::chrono::seconds(s) + std::chrono::milliseconds(ms) )
    {
    }
    explicit TimeSpan(long ticks)
        :
        TimeSpan( ticks * std::chrono::nanoseconds( NanosecondsPerTick() ) )
    {
    }
    TimeSpan(std::chrono::system_clock::duration value)
        :
        _time_span( value )
    {
    }

    TimeSpan(const TimeSpan &other)
        :
        _time_span( other._time_span )
    {
    }
    TimeSpan(TimeSpan &&other)
        :
        _time_span( std::move(other._time_span) )
    {
    }
    TimeSpan &operator =(const TimeSpan &other)
    {
        _time_span = other._time_span;
        return *this;
    }
    TimeSpan &operator =(TimeSpan &&other)
    {
        _time_span = std::move(other._time_span);
        return *this;
    }

    static TimeSpan FromTicks(long value) { return TimeSpan( value ); }
    static TimeSpan FromMicroseconds(long value) { return TimeSpan( std::chrono::microseconds( value ) ); }
    static TimeSpan FromMilliseconds(long milli, long micro)
    {
        return TimeSpan( std::chrono::milliseconds( milli ) + std::chrono::microseconds( micro ) );
    }
    static TimeSpan FromSeconds(long value) { return TimeSpan( std::chrono::seconds( value ) ); }
    static TimeSpan FromMinutes(long value) { return TimeSpan( std::chrono::minutes( value ) ); }
    static TimeSpan FromHours(int value)    { return TimeSpan( std::chrono::hours( value ) ); }
    static TimeSpan FromDays(int value)     { return TimeSpan( std::chrono::days( value ) ); }


    static constexpr int  HoursPerDay() { return 24; }
    static constexpr long MinutesPerDay() { return 1'440; }
    static constexpr long SecondsPerDay() { return 86'400; }
    static constexpr long MillisecondsPerDay() { return 86'400'000; }
    static constexpr long MicrosecondsPerDay() { return 86'400'000'000; }

    static constexpr long MinutesPerHour() { return 60; }
    static constexpr long SecondsPerHour() { return 3'600; }
    static constexpr long MillisecondsPerHour() { return 3'600'000; }
    static constexpr long MicrosecondsPerHour() { return 3'600'000'000; }

    static constexpr long SecondsPerMinute() { return 60; }
    static constexpr long MillisecondsPerMinute() { return 60'000; }
    static constexpr long MicrosecondsPerMinute() { return 60'000'000; }

    static constexpr long MillisecondsPerSecond() { return 1000; }
    static constexpr long MicrosecondsPerSecond() { return 1'000'000; }
    static constexpr long NanosecondsPerSecond() { return 1'000'000'000; }

    static constexpr long MicrosecondsPerMillisecond() { return 1'000; }

    static constexpr long NanosecondsPerTick() { return 100; }

    static constexpr long TicksPerDay() { return 864'000'000'000; }
    static constexpr long TicksPerHour() { return 36'000'000'000; }
    static constexpr long TicksPerMinute() { return 600'000'000; }
    static constexpr long TicksPerSecond() { return 10'000'000; }
    static constexpr long TicksPerMillisecond() { return 10'000; }
    static constexpr long TicksPerMicrosecond() { return 10; }

    static TimeSpan Zero()        { return TimeSpan( std::chrono::system_clock::duration::zero() ); }
    static TimeSpan MinValue()    { return TimeSpan( std::chrono::system_clock::duration::min() ); }
    static TimeSpan MaxValue()    { return TimeSpan( std::chrono::system_clock::duration::max() ); }

    long Ticks() const { return _time_span.count() / NanosecondsPerTick(); }

    constexpr operator std::chrono::system_clock::duration() const { return _time_span; }

    int Days() const;
    int Hours() const;
    int Minutes() const;
    int Seconds() const;
    int Milliseconds() const;
    int Microseconds() const;
    int Nanoseconds() const;

    double TotalDays() const;
    double TotalHours() const;
    double TotalMinutes() const;
    double TotalSeconds() const;
    double TotalMilliseconds() const;
    double TotalMicroseconds() const;
    double TotalNanoseconds() const;

    TimeSpan &operator +=(std::chrono::system_clock::duration duration_to_add)
    {
        _time_span += duration_to_add;
        return *this;
    }

    TimeSpan &operator -=(std::chrono::system_clock::duration duration_to_subtract)
    {
        _time_span -= duration_to_subtract;
        return *this;
    }

    template <class Representation>
    TimeSpan operator *=(const Representation &right)
    {
        _time_span *= static_cast<std::chrono::system_clock::rep>( right );
        return *this;
    }

    template <class Representation>
    TimeSpan operator /=(const Representation &right)
    {
        _time_span /= static_cast<std::chrono::system_clock::rep>( right );
        return *this;
    }

    TimeSpan Add(const TimeSpan &time_span) const;
    TimeSpan Subtract(const TimeSpan &time_span) const;
    TimeSpan Multiply(double scalar) const;
    TimeSpan Divide(double scalar) const;

    static constexpr int Compare(const TimeSpan &left, const TimeSpan &right)
    {
        auto result{ left <=> right };

        if ( result == std::strong_ordering::less )
            return -1;
        else if ( result == std::strong_ordering::equal )
            return 0;
        else
            return 1;
    }

    int CompareTo(const TimeSpan &other) const { return Compare( *this, other); }

    static constexpr bool Equals(TimeSpan &left, TimeSpan &right) { return left == right; }

    TimeSpan Duration() const { return TimeSpan( std::chrono::abs( _time_span ) ); }
    TimeSpan Negate() const { return -*this; }

    std::string ToString() const;
protected:
    std::chrono::system_clock::duration _time_span{ std::chrono::system_clock::duration::zero() };


    friend constexpr bool operator ==(const TimeSpan &left, const TimeSpan &right)
    {
        return left._time_span == right._time_span;
    }

    friend constexpr std::strong_ordering operator <=>(const TimeSpan &left, const TimeSpan &right)
    {
        return left._time_span <=> right._time_span;
    }

    template <typename Rep, typename Period>
    friend TimeSpan operator +(const TimeSpan &left, const std::chrono::duration<Rep, Period> &right_as_duration)
    {
        return TimeSpan( left._time_span + right_as_duration );
    }

    friend TimeSpan operator +(const TimeSpan &left, const TimeSpan &right)
    {
        return TimeSpan( left._time_span + right._time_span );
    }

    template <typename Rep, typename Period>
    friend TimeSpan operator -(const TimeSpan &left, const std::chrono::duration<Rep, Period> &right_as_duration)
    {
        return TimeSpan( left._time_span - right_as_duration );
    }

    friend TimeSpan operator -(const TimeSpan &left, const TimeSpan &right)
    {
        return TimeSpan( left._time_span - right._time_span );
    }

    template <class Representation>
    friend TimeSpan operator *(const TimeSpan &left, const Representation &right)
    {
        return TimeSpan( left._time_span * static_cast<std::chrono::system_clock::rep>( right ) );
    }

    template <class Representation>
    friend TimeSpan operator *(const Representation &left, const TimeSpan &right)
    {
        return TimeSpan( static_cast<std::chrono::system_clock::rep>( left ) * right._time_span );
    }

    template <class Representation>
    friend TimeSpan operator /(const TimeSpan &left, const Representation &right)
    {
        return TimeSpan( left._time_span / static_cast<std::chrono::system_clock::rep>( right ) );
    }

    friend TimeSpan operator -(const TimeSpan &ts)
    {
        return TimeSpan( -ts._time_span );
    }

    friend TimeSpan operator +(const TimeSpan &ts)
    {
        return TimeSpan( +ts );
    }
};

}

namespace System
{

int TimeSpan::Days() const
{
    bool negative = (_time_span.count() < 0);
    long d = (negative) ? std::chrono::ceil<std::chrono::days>( _time_span ).count() : std::chrono::floor<std::chrono::days>( _time_span ).count();

    return static_cast<int>(d);
}

int TimeSpan::Hours() const
{
    bool negative = (_time_span.count() < 0);
    long h = (negative) ? std::chrono::ceil<std::chrono::hours>( _time_span ).count() : std::chrono::floor<std::chrono::hours>( _time_span ).count();
    std::ldiv_t  d = std::div( h, static_cast<long>(HoursPerDay()) );

    // POSTCONDITION( d.rem >= -23 );
    // POSTCONDITION( d.rem <=  23 );

    return d.rem;
}

int TimeSpan::Minutes() const
{
    bool negative = (_time_span.count() < 0);
    long m = (negative) ? std::chrono::ceil<std::chrono::minutes>( _time_span ).count() : std::chrono::floor<std::chrono::minutes>( _time_span ).count();
    std::ldiv_t d = std::div( m, MinutesPerHour() );

    // POSTCONDITION( d.rem >= -59 );
    // POSTCONDITION( d.rem <=  59 );

    return d.rem;
}

int TimeSpan::Seconds() const
{
    bool negative = (_time_span.count() < 0);
    long s = (negative) ? std::chrono::ceil<std::chrono::seconds>( _time_span ).count() : std::chrono::floor<std::chrono::seconds>( _time_span ).count();
    std::ldiv_t d = std::div( s, SecondsPerMinute() );

    // POSTCONDITION( d.rem >= -59 );
    // POSTCONDITION( d.rem <=  59 );

    return d.rem;
}

int TimeSpan::Milliseconds() const
{
    bool negative = (_time_span.count() < 0);
    long ms = (negative) ? std::chrono::ceil<std::chrono::milliseconds>( _time_span ).count() : std::chrono::floor<std::chrono::milliseconds>( _time_span ).count();
    std::ldiv_t d = std::div( ms, MillisecondsPerSecond() );

    // POSTCONDITION( d.rem >= -999 );
    // POSTCONDITION( d.rem <=  999 );

    return d.rem;
}

int TimeSpan::Microseconds() const
{
    bool negative = (_time_span.count() < 0);
    long ms = (negative) ? std::chrono::ceil<std::chrono::microseconds>( _time_span ).count() : std::chrono::floor<std::chrono::microseconds>( _time_span ).count();
    std::ldiv_t d = std::div( ms, MicrosecondsPerSecond() );

    // POSTCONDITION( d.rem >= -999'999 );
    // POSTCONDITION( d.rem <=  999'999 );

    return d.rem;
}

int TimeSpan::Nanoseconds() const
{
    // System clock is typically in nanoseconds, so we can just use the count() directly
    long ns = _time_span.count();
    std::ldiv_t d = std::div( ns, NanosecondsPerSecond() );

    // POSTCONDITION( d.rem >= -99'999'999 );
    // POSTCONDITION( d.rem <=  99'999'999 );

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
    // Detect a potential wrap-around...
    if ( Ticks() >= 0 )
    {
        if ( MaxValue().Ticks() - Ticks() < time_span.Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting TimeSpan is greater than TimeSpan::MaxValue") );
    }
    else
    {
        if ( time_span.Ticks() < MinValue().Ticks() - Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting DateTime is less than DateTime::MinValue") );
        
    }
    return *this + time_span;
}

TimeSpan TimeSpan::Subtract(const TimeSpan &time_span) const
{
    // Detect a potential wrap-around...
    if ( Ticks() >= 0 )
    {
        if ( MinValue().Ticks() + Ticks() < time_span.Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting DateTime is less than DateTime::MinValue") );
    }
    else
    {
        if ( time_span.Ticks() < MaxValue().Ticks() - Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting TimeSpan is greater than TimeSpan::MaxValue") );
        
    }
    return *this - time_span;
}

TimeSpan TimeSpan::Multiply(double scalar) const
{
    // using namespace std::literals;

    // // Detect a potential wrap-around...
    // long long this_count = _time_span.count();
    // long long other_count = time_span._time_span.count();
    // long long new_value = this_count * other_count;

    // if ( new_value > system_clock::duration( MaxValue() ).count() )
    //     ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting TimeSpan is greater than TimeSpan::MaxValue"sv) );
    // else
    // {
    //     if ( new_value < system_clock::duration( MinValue() ).count() )
    //         ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is less than DateTime::MinValue"sv) );
    // }

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
export
template <>
struct std::formatter<System::TimeSpan>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const System::TimeSpan &object, FormatContext &ctx) const
    {
        return std::format_to( ctx.out(), "{}", std::chrono::system_clock::duration(object) );
    }
};