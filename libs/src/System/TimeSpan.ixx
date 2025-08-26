export module System:TimeSpan;

import <chrono>;
import <compare>;
import <string>;

namespace System
{

export
class TimeSpan
{
public:
    constexpr TimeSpan() = default;
    explicit TimeSpan(int hours, int minutes, int seconds) : TimeSpan(0, hours, minutes, seconds) { }
    explicit TimeSpan(int days, int hours, int minutes, int seconds);
    explicit TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds);
    explicit TimeSpan(long ticks) : TimeSpan( ticks * std::chrono::nanoseconds( NanosecondsPerTick() ) ) { }
    TimeSpan(std::chrono::system_clock::duration value) : _time_span( value ) { }

    TimeSpan(const TimeSpan &) = default;
    TimeSpan(TimeSpan &&) = default;
    TimeSpan &operator =(const TimeSpan &) = default;
    TimeSpan &operator =(TimeSpan &&) = default;

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