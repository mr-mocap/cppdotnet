export module System:DateOnly;

import System:DayOfWeek;
import System:DateTime;
import System:Exception;

// #include "System/Private/private.hpp"
import <chrono>;
import <compare>;
import <string>;
import <format>;



namespace System
{

export
class DateOnly
{
public:
    DateOnly() = default;
    explicit constexpr DateOnly(int year, int month, int day)
        :
        _year_month_day( std::chrono::year(year), std::chrono::month(month), std::chrono::day(day) )
    {
        // POSTCONDITION( year <= 9999 );
        // POSTCONDITION( year >= 1 );
        // POSTCONDITION( month >= 1 );
        // POSTCONDITION( month <= 12 );
        // POSTCONDITION( day >= 1 );
        // POSTCONDITION( day <= 31 );
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

export
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

namespace System
{

int DateOnly::DayOfYear() const
{
    sys_days temp_days{ _year_month_day };
    years    current_year = floor<years>( temp_days.time_since_epoch() );
    days     d            = duration_cast<days>( temp_days.time_since_epoch() - current_year );

    // Let's add 1 since the subtraction puts us at a 0-based number
    return static_cast<int>( d.count() + 1 );
}

DateOnly DateOnly::AddDays(int num_days) const
{
    using namespace std::literals;

    sys_days as_time_point{ sys_days( _year_month_day ) };
    sys_days new_time_point = as_time_point + days( num_days );
    DateOnly new_date_only{ new_time_point };

    if ( new_date_only <= MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_days"sv, "Parameter is less than minimum allowed value"sv ) );
    else if ( new_date_only >= MaxValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_days"sv, "Parameter is greater than minimum allowed value"sv ) );
    
    return new_date_only;
}

DateOnly DateOnly::AddMonths(int num_months) const
{
    using namespace std::literals;

    DateOnly new_date_only( _year_month_day + std::chrono::months( num_months ) );

    if ( new_date_only <= MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_months"sv, "Parameter is less than minimum allowed value"sv ) );
    else if ( new_date_only >= MaxValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_months"sv, "Parameter is greater than minimum allowed value"sv ) );
    
    return new_date_only;
}

DateOnly DateOnly::AddYears(int num_years) const
{
    using namespace std::literals;

    DateOnly new_date_only( _year_month_day + years( num_years ) );

    if ( new_date_only <= MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_years"sv, "Parameter is less than minimum allowed value"sv ) );
    else if ( new_date_only >= MaxValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_years"sv, "Parameter is greater than minimum allowed value"sv ) );
    
    return new_date_only;
}

int DateOnly::CompareTo(const DateOnly &other) const
{
    auto result{ *this <=> other };

    if ( result == std::strong_ordering::less )
        return -1;
    else if ( result == std::strong_ordering::equal )
        return 0;
    else
        return 1;
}

DateOnly DateOnly::FromDateTime(const DateTime &dt)
{
    return DateOnly{ dt.Year(), dt.Month(), dt.Day() };
}

DateOnly DateOnly::FromDayNumber(int day_number)
{
    return DateOnly::MinValue().AddDays( day_number );
}

void DateOnly::Deconstruct(int &year, int &month, int &day)
{
    year = Year();
    month = Month();
    day = Day();
}

std::string DateOnly::ToString() const
{
    return std::format("{}", _year_month_day);
}

}