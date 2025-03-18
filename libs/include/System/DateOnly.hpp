#pragma once

#include "System/DateTime.hpp"
#include "System/Private/private.hpp"
#include <chrono>
#include <compare>


namespace System
{

class DateOnly
{
public:
    explicit constexpr DateOnly(int year, int month, int day)
        :
        DateOnly( std::chrono::year(year), std::chrono::month(month), std::chrono::day(day) )
    {
    }

    explicit constexpr DateOnly(const std::chrono::year &y, const std::chrono::month &m, const std::chrono::day &d)
        :
        _year_month_day( y, m, d )
    {
        POSTCONDITION( *this <= MaxValue() );
        POSTCONDITION( *this >= MinValue() );
    }

    constexpr DateOnly(const std::chrono::year_month_day &ymd)
        :
        _year_month_day( ymd )
    {
    }

    DateOnly(const DateOnly &) = default;
    DateOnly &operator =(const DateOnly &) = default;

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
        int temp{ _year_month_day.year() };

        return temp;
    }

    constexpr int DayNumber() const
    {
        std::chrono::sys_days num_days{ _year_month_day };

        return static_cast<int>( num_days.time_since_epoch().count() );
    }

    enum DayOfWeek DayOfWeek() const
    {
        std::chrono::weekday wd{ std::chrono::sys_days( _year_month_day ) };

        return static_cast<enum DayOfWeek>( wd.c_encoding() );
    }

    int DayOfYear() const;

    static constexpr DateOnly MaxValue() { return DateOnly( std::chrono::year(1), std::chrono::month(1), std::chrono::day(1) ); }
    static constexpr DateOnly MinValue() { return DateOnly( std::chrono::year(9999), std::chrono::month(12), std::chrono::day(31) ); }

    static DateOnly FromDateTime(const DateTime &dt);

    DateOnly AddDays(int num_days);
    DateOnly AddMonths(int num_months);
    DateOnly AddYears(int num_years);

    int CompareTo(const DateOnly &other) const;
    bool Equals(const DateOnly &other) const { return *this == other; }

    void Deconstruct(int &year, int &month, int &day);
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
};

}