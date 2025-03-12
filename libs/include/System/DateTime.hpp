#pragma once

#include "System/DayOfWeek.hpp"
#include "System/DateTimeKind.hpp"
#include "System/TimeSpan.hpp"
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
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int milliseconds = 0);
    constexpr DateTime(std::chrono::system_clock::time_point tp) : _point_in_time( tp ) { }

    DateTime(const DateTime &) = default;
    DateTime(DateTime &&) = default;

    DateTime &operator =(const DateTime &) = default;
    DateTime &operator =(DateTime &&) = default;

    DateTime Date() const;
    TimeSpan TimeOfDay() const;

    DateTimeKind Kind() const { return _kind; }

    int Year() const;
    int Month() const;
    int Day() const;

    int Hour() const;
    int Minute() const;
    int Second() const;
    int Millisecond() const;
    int Microsecond() const;
    int Nanosecond() const;

    long Ticks() const;

    enum DayOfWeek DayOfWeek() const;
               int DayOfYear() const;

    static DateTime Now();
    static DateTime UtcNow();
    static DateTime Today();

    static constexpr DateTime MaxValue() { return DateTime( std::chrono::system_clock::time_point::max() ); }
    static constexpr DateTime MinValue() { return DateTime( std::chrono::system_clock::time_point::min() ); }
    static constexpr DateTime UnixEpoch() { return DateTime( std::chrono::system_clock::time_point() ); }

    std::string ToString() const;

    constexpr DateTime &operator +=(std::chrono::system_clock::duration time_span)
    {
        _point_in_time += time_span;
        return *this;
    }

    constexpr DateTime &operator -=(std::chrono::system_clock::duration time_span)
    {
        _point_in_time -= time_span;
        return *this;
    }

    DateTime Add(TimeSpan time_span) const;

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
    std::chrono::system_clock::time_point _point_in_time = std::chrono::system_clock::time_point::min();
    DateTimeKind _kind = DateTimeKind::Unspecified;
    

    friend constexpr bool operator ==(const DateTime &left, const DateTime &right)
    {
        return left._point_in_time == right._point_in_time;
    }

    friend constexpr std::strong_ordering operator <=>(const DateTime &left, const DateTime &right)
    {
        return left._point_in_time <=> right._point_in_time;
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
        return DateTime( left ) -= right;
    }

    friend TimeSpan operator -(const DateTime &left, const DateTime &right)
    {
        return { left._point_in_time.time_since_epoch() - right._point_in_time.time_since_epoch() };
    }

    friend DateTime operator -(const DateTime &left, std::chrono::system_clock::duration right)
    {
        return DateTime( left ) -= right;
    }
};

}