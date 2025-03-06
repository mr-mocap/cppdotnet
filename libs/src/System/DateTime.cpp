#include "System/DateTime.hpp"
#include <format>

using namespace std::chrono;

namespace System
{

DateTime::DateTime(int y, int m, int d)
    :
    _point_in_time( sys_days( year_month_day( year(y) / month(m) / day(d) ) ) )
{
}

int DateTime::Year() const
{
    auto dp = floor<days>(_point_in_time);
    year_month_day ymd{ dp };

    return static_cast<int>(ymd.year());
}

int DateTime::Month() const
{
    auto dp = floor<days>(_point_in_time);
    year_month_day ymd{ dp };
    unsigned int temp{ ymd.month() };

    return static_cast<int>(temp);
}

int DateTime::Day() const
{
    auto dp = floor<days>(_point_in_time);
    year_month_day ymd{ dp };
    unsigned int temp{ ymd.day() };

    return static_cast<int>(temp);
}

int DateTime::Hour() const
{
#if 0
    hh_mm_ss time{ floor<milliseconds>(_point_in_time) };

    return time.hours().count();
#else
    return 0;
#endif
}

enum DayOfWeek DateTime::DayOfWeek() const
{
    auto dp = floor<days>(_point_in_time);
    year_month_day ymd{ dp };
    weekday wd{ sys_days( ymd ) };

    return static_cast<enum DayOfWeek>( wd.c_encoding() );
}

DateTime DateTime::Now()
{
    return DateTime( system_clock::now() );
}

std::string DateTime::ToString() const
{
    return std::format("{}", _point_in_time);
}

}