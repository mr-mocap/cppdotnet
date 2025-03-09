#pragma once

#include "System/DayOfWeek.hpp"
#include "System/DateTimeKind.hpp"
#include "System/TimeSpan.hpp"
#include <cstddef>
#include <chrono>
#include <string>
#include <compare>


namespace System
{

class DateTime
{
public:
    DateTime() = delete;
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int milliseconds = 0);
    DateTime(std::chrono::system_clock::time_point tp) : _point_in_time( tp ) { }

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

    static DateTime MaxValue();
    static DateTime MinValue();
    static DateTime UnixEpoch();

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

protected:
    std::chrono::system_clock::time_point _point_in_time;
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

    friend DateTime operator -(const DateTime &left, const TimeSpan &right)
    {
        return DateTime( left ) -= right;
    }
};

}