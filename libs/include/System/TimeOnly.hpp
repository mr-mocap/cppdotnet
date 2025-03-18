#pragma once

#include "System/TimeSpan.hpp"
#include "System/Private/private.hpp"
#include <chrono>
#include <compare>


namespace System
{

class TimeOnly
{
public:
    TimeOnly() = default;
    constexpr explicit TimeOnly(int h, int m, int s = 0, int ms = 0, int micros = 0)
        :
        _time_span( std::chrono::hours(h) +
                    std::chrono::minutes(m) +
                    std::chrono::seconds(s) +
                    std::chrono::milliseconds(ms) +
                    std::chrono::microseconds(micros) )
        {
            POSTCONDITION( h >= 0 );
            POSTCONDITION( h <= 23 );

            POSTCONDITION( m >= 0 );
            POSTCONDITION( m <= 59 );

            POSTCONDITION( s >= 0 );
            POSTCONDITION( s <= 59 );

            POSTCONDITION( ms >= 0 );
            POSTCONDITION( ms <= 999 );

            POSTCONDITION( micros >= 0 );
            POSTCONDITION( micros <= 999'999 );
        }
    constexpr explicit TimeOnly(long ticks) : _time_span( ticks ) { }
    constexpr TimeOnly(std::chrono::system_clock::duration value) : _time_span( value ) { }

    TimeOnly(const TimeOnly &) = default;
    TimeOnly &operator =(const TimeOnly &) = default;

    int Hour() const { return _time_span.Hours(); }
    int Minute() const { return _time_span.Minutes(); }
    int Second() const { return _time_span.Seconds(); }
    int Millisecond() const { return _time_span.Milliseconds(); }
    int Microsecond() const { return _time_span.Microseconds(); }
    int Nanosecond() const { return _time_span.Nanoseconds(); }

    static TimeOnly MaxValue() { return TimeOnly(23, 59, 59, 999, 999); }
    static TimeOnly MinValue() { return TimeOnly(); }

    TimeOnly Add(const TimeSpan &value) const { return TimeOnly( *this ) + value; }
    TimeOnly Add(const TimeSpan &value, int &out_excess_days) const;
    TimeOnly AddHours(double hours) const;
    TimeOnly AddHours(double hours, int &out_excess_days) const;
    TimeOnly AddMinutes(double minutes) const;
    TimeOnly AddMinutes(double minutes, int &out_excess_minutes) const;

    int CompareTo(const TimeOnly &other) const;
    bool Equals(const TimeOnly &other) const { return _time_span == other._time_span; }

    void Deconstruct(int &hour, int &minute, int &second, int &millisecond, int &microsecond) const;
    void Deconstruct(int &hour, int &minute, int &second, int &millisecond) const;
    void Deconstruct(int &hour, int &minute, int &second) const;
    void Deconstruct(int &hour, int &minute) const;
protected:
    TimeSpan _time_span;


    TimeOnly(const TimeSpan &init) : _time_span( init ) { }

    friend bool operator ==(const TimeOnly &left, const TimeOnly &right)
    {
        return left._time_span == right._time_span;
    }

    friend std::strong_ordering operator <=>(const TimeOnly &left, const TimeOnly &right)
    {
        return left._time_span <=> right._time_span;
    }

    friend TimeOnly operator +(const TimeOnly &left, const TimeSpan &right)
    {
        return TimeOnly( left._time_span + right );
    }
};

}