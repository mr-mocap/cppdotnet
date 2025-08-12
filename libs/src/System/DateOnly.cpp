module

module System;

import "System/DateOnly.hpp";
import "System/DateTime.hpp";
import "System/Exception.hpp";

using namespace std::chrono;

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