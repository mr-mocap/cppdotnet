#pragma once

#include "System/DayOfWeek.hpp"
#include "System/TimeSpan.hpp"
#include "System/Private/private.hpp"
#include <chrono>
#include <compare>


namespace System
{

class DateTime;

class DateOnly
{
public:
    constexpr DateOnly() = default;
    explicit constexpr DateOnly(int year, int month, int day)
        :
        _year_month_day( std::chrono::year(year), std::chrono::month(month), std::chrono::day(day) )
    {
        POSTCONDITION( year <= 9999 );
        POSTCONDITION( year >= 1 );
        POSTCONDITION( month >= 1 );
        POSTCONDITION( month <= 12 );
        POSTCONDITION( day >= 1 );
        POSTCONDITION( day <= 31 );
    }

    constexpr DateOnly(const std::chrono::year_month_day &ymd)
                  :
                  _year_month_day( ymd )
              {
              }

    constexpr DateOnly(const std::chrono::sys_days &d)
                  :
                  _year_month_day( std::chrono::year_month_day( d ) )
                  {
                  }

    DateOnly(const DateOnly &) = default;
    DateOnly &operator =(const DateOnly &) = default;
    DateOnly(DateOnly &&) = default;
    DateOnly &operator =(DateOnly &&) = default;

    constexpr int Day() const
    {
        unsigned int temp{ _year_month_day.day() };

        return static_cast<int>( temp );
    }

    constexpr int Month() const
    {
        unsigned int temp{ _year_month_day.month() };

        return static_cast<int>( temp );
    }

    constexpr int Year() const
    {
        return static_cast<int>( _year_month_day.year() );
    }

    constexpr int DayNumber() const
    {
        std::chrono::sys_days num_days{ _year_month_day };

        return static_cast<int>( num_days.time_since_epoch().count() );
    }

    constexpr enum DayOfWeek DayOfWeek() const
    {
        std::chrono::weekday wd{ std::chrono::sys_days( _year_month_day ) };

        return static_cast<enum DayOfWeek>( wd.c_encoding() );
    }

    int DayOfYear() const;

    static constexpr DateOnly MinValue() { return DateOnly( 1, 1, 1 ); }
    static constexpr DateOnly MaxValue() { return DateOnly( 9999, 12, 31 ); }

    static DateOnly FromDateTime(const DateTime &dt);

    DateOnly AddDays(int num_days) const;
    DateOnly AddMonths(int num_months) const;
    DateOnly AddYears(int num_years) const;

    int CompareTo(const DateOnly &other) const;
    bool Equals(const DateOnly &other) const { return *this == other; }

    void Deconstruct(int &year, int &month, int &day);

    std::string ToString() const;

    operator std::chrono::sys_days() const { return _year_month_day; }
protected:
    std::chrono::year_month_day _year_month_day;


    friend constexpr bool operator ==(const DateOnly &left, const DateOnly &right)
    {
        return left._year_month_day == right._year_month_day;
    }

    friend constexpr std::strong_ordering operator <=>(const DateOnly &left, const DateOnly &right)
    {
        return left._year_month_day <=> right._year_month_day;
    }

    friend constexpr TimeSpan operator -(const DateOnly &left, const DateOnly &right)
    {
        std::chrono::sys_days left_days = left._year_month_day;
        std::chrono::sys_days right_days = right._year_month_day;
        std::chrono::sys_days result = left_days - right_days.time_since_epoch();

        return TimeSpan( result.time_since_epoch() );
    }
};

}