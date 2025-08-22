#include "System/DayOfWeek.hpp"
#include "System/Private/private.hpp"
#include <chrono>
#include <compare>
#include <string>
#include <format>


namespace System
{

class DateTime;

class DateOnly
{
public:
    DateOnly() = default;
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

    constexpr DateOnly(const DateOnly &) = default;
    constexpr DateOnly &operator =(const DateOnly &) = default;
    constexpr DateOnly(DateOnly &&) = default;
    constexpr DateOnly &operator =(DateOnly &&) = default;

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

    constexpr enum System::DayOfWeek DayOfWeek() const
    {
        std::chrono::weekday wd{ std::chrono::sys_days( _year_month_day ) };

        return static_cast<enum System::DayOfWeek>( wd.c_encoding() );
    }

    int DayOfYear() const;

    static constexpr DateOnly MinValue() { return DateOnly( 1, 1, 1 ); }
    static constexpr DateOnly MaxValue() { return DateOnly( 9999, 12, 31 ); }

    static DateOnly FromDateTime(const System::DateTime &dt);
    static DateOnly FromDayNumber(int day_number);

    DateOnly AddDays(int num_days) const;
    DateOnly AddMonths(int num_months) const;
    DateOnly AddYears(int num_years) const;

    int CompareTo(const DateOnly &other) const;
    bool Equals(const DateOnly &other) const { return *this == other; }

    void Deconstruct(int &year, int &month, int &day);

    std::string ToString() const;
#if 0
    DateTime ToDateTime(const TimeOnly &time_only) const
    {
        return DateTime( *this, time_only );
    }
#endif

    operator std::chrono::sys_days() const { return _year_month_day; }
    operator std::chrono::year_month_day() const { return _year_month_day; }
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

template <>
struct std::formatter<System::DateOnly>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const System::DateOnly &object, FormatContext &ctx) const
    {
        return std::format_to( ctx.out(), "{}", object.ToString() );
    }
};