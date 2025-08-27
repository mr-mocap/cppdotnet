module;

module System:DateOnly;

import System:Exception;
import System:DateTime;
import System:DayOfWeek;
import <chrono>;
import <format>;

namespace System
{

DateOnly::DateOnly()
{
}

DateOnly::~DateOnly()
{
}

DateOnly(int year, int month, int day)
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

DateOnly(const std::chrono::year_month_day &ymd)
    :
    _year_month_day( ymd )
{
}

DateOnly(const std::chrono::sys_days &d)
    :
    _year_month_day( std::chrono::year_month_day( d ) )
{
}

DateOnly::DateOnly(const DateOnly &other)
    :
    _year_month_day( other._year_month_day )
{
}

DateOnly &DateOnly::operator =(const DateOnly &other)
{
    _year_month_day = other._year_month_day;
    return *this;
}

DateOnly::DateOnly(DateOnly &&other)
    :
    _year_month_day( std::move(other._year_month_day) )
{
}

DateOnly &DateOnly::operator =(DateOnly &&other)
{
    _year_month_day = std::move(other._year_month_day);
    return *this;
}

int DateOnly::DayOfYear() const
{
    using namespace std::chrono;

    sys_days temp_days{ _year_month_day };
    years    current_year = floor<years>( temp_days.time_since_epoch() );
    days     d            = duration_cast<days>( temp_days.time_since_epoch() - current_year );

    // Let's add 1 since the subtraction puts us at a 0-based number
    return static_cast<int>( d.count() + 1 );
}

DateOnly DateOnly::AddDays(int num_days) const
{
    using namespace std::chrono;

    sys_days as_time_point{ sys_days( _year_month_day ) };
    sys_days new_time_point = as_time_point + days( num_days );
    DateOnly new_date_only{ new_time_point };

    if ( new_date_only <= MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_days", "Parameter is less than minimum allowed value" ) );
    else if ( new_date_only >= MaxValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_days", "Parameter is greater than minimum allowed value" ) );
    
    return new_date_only;
}

DateOnly DateOnly::AddMonths(int num_months) const
{
    DateOnly new_date_only( _year_month_day + std::chrono::months( num_months ) );

    if ( new_date_only <= MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_months", "Parameter is less than minimum allowed value" ) );
    else if ( new_date_only >= MaxValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_months", "Parameter is greater than minimum allowed value" ) );
    
    return new_date_only;
}

DateOnly DateOnly::AddYears(int num_years) const
{
    DateOnly new_date_only( _year_month_day + std::chrono::years( num_years ) );

    if ( new_date_only <= MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_years", "Parameter is less than minimum allowed value" ) );
    else if ( new_date_only >= MaxValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_years", "Parameter is greater than minimum allowed value" ) );
    
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

DateOnly DateOnly::FromDateTime(const DateTime &dt)
{
    return DateOnly{ dt.Year(), dt.Month(), dt.Day() };
}

std::string DateOnly::ToString() const
{
    return std::format("{}", _year_month_day);
}

enum System::DayOfWeek DayOfWeek() const
{
    std::chrono::weekday wd{ std::chrono::sys_days( _year_month_day ) };

    return static_cast<enum System::DayOfWeek>( wd.c_encoding() );
}

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