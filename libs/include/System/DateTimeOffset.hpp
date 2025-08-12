#pragma once

import "System/TimeSpan.hpp";
import "System/DateTime.hpp";
import "System/DayOfWeek.hpp";


namespace System
{

class DateTimeOffset
{
public:
    constexpr DateTimeOffset() = default;
    constexpr DateTimeOffset(const System::DateTime &dt) : _date_time( dt ) { }
    constexpr DateTimeOffset(const System::DateTime &dt, const System::TimeSpan &offset) : _date_time( dt ), _offset_from_utc( offset ) { }

    const System::DateTime &DateTime() const { return _date_time; }
    const System::TimeSpan &Offset() const { return _offset_from_utc; }

    System::DateTime Date() const { return _date_time.Date(); }

    constexpr enum DayOfWeek DayOfWeek() const { return _date_time.DayOfWeek(); }
                         int DayOfYear() const { return _date_time.DayOfYear(); }
    
    int      Year() const { return _date_time.Year(); }
    int      Month() const { return _date_time.Month(); }
    int      Day() const { return _date_time.Day(); }
    int      Hour() const { return _offset_from_utc.Hours(); }
    int      Minute() const { return _offset_from_utc.Minutes(); }
    int      Second() const { return _offset_from_utc.Seconds(); }
    int      Millisecond() const { return _offset_from_utc.Milliseconds(); }
    int      Microsecond() const { return _offset_from_utc.Microseconds(); }
    int      Nanosecond() const { return _offset_from_utc.Nanoseconds(); }

    long     Ticks() const { return _date_time.Ticks(); }

    static constexpr DateTimeOffset MinValue()  { return DateTimeOffset( System::DateTime::MinValue() ); }
    static constexpr DateTimeOffset MaxValue()  { return DateTimeOffset( System::DateTime::MaxValue() ); }
    static           DateTimeOffset UnixEpoch() { return DateTimeOffset( System::DateTime::UnixEpoch() ); }

    static           DateTimeOffset Now();
    static           DateTimeOffset UtcNow();
protected:
    System::DateTime _date_time;
    System::TimeSpan _offset_from_utc;
};

}