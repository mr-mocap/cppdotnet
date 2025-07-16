#pragma once

#include "System/DayOfWeek.hpp"
#include "System/DateTimeKind.hpp"
#include "System/TimeSpan.hpp"
#include "System/DateOnly.hpp"
#include "System/TimeOnly.hpp"
#include "System/Exception.hpp"
#include <cstddef>
#include <chrono>
#include <string>
#include <compare>


namespace System
{

class DateTime
{
public:
    constexpr DateTime() = default;
    constexpr DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int milliseconds = 0)
                  :
                  _date_only( year, month, day ),
                  _time_only( hour, minute, second, milliseconds )
              {
              }
    constexpr DateTime(const DateOnly &date_only, const TimeOnly &time_only)
                  :
                  _date_only( date_only ),
                  _time_only( time_only)
              {
              }
    //constexpr DateTime(std::chrono::system_clock::time_point tp) : _point_in_time( tp ) { }

    constexpr DateTime(const DateTime &) = default;
    constexpr DateTime(DateTime &&) = default;

    constexpr DateTime &operator =(const DateTime &) = default;
    constexpr DateTime &operator =(DateTime &&) = default;

    constexpr DateTime Date() const { return DateTime( _date_only, TimeOnly() ); }
    constexpr TimeSpan TimeOfDay() const { return _time_only.ToTimeSpan(); }

    constexpr DateTimeKind Kind() const { return _kind; }

    constexpr int Year() const  { return _date_only.Year(); }
    constexpr int Month() const { return _date_only.Month(); }
    constexpr int Day() const   { return _date_only.Day(); }

    int Hour() const { return _time_only.Hour(); }
    int Minute() const { return _time_only.Minute(); }
    int Second() const { return _time_only.Second(); }
    int Millisecond() const { return _time_only.Millisecond(); }
    int Microsecond() const { return _time_only.Microsecond(); }
    int Nanosecond() const { return _time_only.Nanosecond(); }

    long Ticks() const;

    constexpr enum System::DayOfWeek DayOfWeek() const { return _date_only.DayOfWeek(); }
               int DayOfYear() const { return _date_only.DayOfYear(); }

    static DateTime Now();
    static DateTime UtcNow();
    static DateTime Today();
    static DateTime UnixEpoch();

    static constexpr DateTime MinValue()  { return DateTime( DateOnly::MinValue(), TimeOnly::MinValue() ); }
    static constexpr DateTime MaxValue()  { return DateTime( DateOnly::MaxValue(), TimeOnly::MaxValue() ); }

    std::string ToString() const;

    DateTime &operator +=(const TimeSpan &time_span) { return _accumulate( time_span ); }
    DateTime &operator -=(const TimeSpan &time_span) { return _accumulate( -time_span ); }
    DateTime &operator +=(std::chrono::system_clock::duration time_duration) { return _accumulate( time_duration ); }
    DateTime &operator -=(std::chrono::system_clock::duration time_duration) { return _accumulate( -time_duration ); }

    DateTime Add(const TimeSpan &time_span) const;
    TimeSpan Subtract(const DateTime &other_date) const;
    DateTime Subtract(const TimeSpan &other_time_span) const;

    DateTime AddYears(int y) const;
    DateTime AddMonths(int m) const;
    DateTime AddDays(double d) const;
    DateTime AddHours(double h) const;
    DateTime AddMinutes(double m) const;
    DateTime AddSeconds(double s) const;
    DateTime AddMilliseconds(double ms) const;
    DateTime AddMicroseconds(double micro_seconds) const;
    DateTime AddTicks(long ticks) const;

    static int Compare(const DateTime &t1, const DateTime &t2);

    int CompareTo(const DateTime &other) const { return Compare( *this, other); }
protected:
    DateOnly     _date_only{ DateOnly::MinValue() };
    TimeOnly     _time_only{ TimeOnly::MinValue() };
    DateTimeKind _kind = DateTimeKind::Unspecified;
    
    DateTime &_accumulate(std::chrono::system_clock::duration time_duration);

    friend constexpr bool operator ==(const DateTime &left, const DateTime &right)
    {
        return (left._date_only == right._date_only) && (left._time_only == right._time_only);
    }

    friend constexpr std::strong_ordering operator <=>(const DateTime &left, const DateTime &right)
    {
        auto result = left._date_only <=> right._date_only;

        if ( result != std::strong_ordering::equal )
            return result; // The date's aren't equal so just use that
        
        return left._time_only <=> right._time_only; // Use the time since they are the same day
    }

    friend DateTime operator +(const DateTime &left, const TimeSpan &right)
    {
        return DateTime( left ) += right;
    }

    friend DateTime operator +(const DateTime &left, std::chrono::system_clock::duration right)
    {
        return DateTime( left ) += right;
    }

    friend DateTime operator -(const DateTime &left, const TimeSpan &right)
    {
        return left.Subtract( right );
    }

    friend TimeSpan operator -(const DateTime &left, const DateTime &right)
    {
        return left.Subtract( right );
    }

    friend DateTime operator -(const DateTime &left, std::chrono::system_clock::duration right)
    {
        return DateTime( left ) -= right;
    }
};

}

template <>
struct std::formatter<System::DateTime>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const System::DateTime &object, FormatContext &ctx) const
    {
        return std::format_to( ctx.out(), "{}", object.ToString());
    }
};