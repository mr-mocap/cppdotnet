module System:TimeOnly;

import System:DateTime;
import <format>;
import <chrono>;
import <cmath>;

namespace System
{

TimeOnly::TimeOnly()
{
}

TimeOnly(int h, int m, int s, int ms, int micros)
    :
    _time_span( std::chrono::hours(h) +
                std::chrono::minutes(m) +
                std::chrono::seconds(s) +
                std::chrono::milliseconds(ms) +
                std::chrono::microseconds(micros) )
{
    // POSTCONDITION( h >= 0 );
    // POSTCONDITION( h <= 23 );

    // POSTCONDITION( m >= 0 );
    // POSTCONDITION( m <= 59 );

    // POSTCONDITION( s >= 0 );
    // POSTCONDITION( s <= 59 );

    // POSTCONDITION( ms >= 0 );
    // POSTCONDITION( ms <= 999 );

    // POSTCONDITION( micros >= 0 );
    // POSTCONDITION( micros <= 999'999 );
}

TimeOnly::TimeOnly(long ticks)
    :
    _time_span( ticks )
{
}

TimeOnly::~TimeOnly()
{
}

TimeOnly TimeOnly::Add(const TimeSpan &value, int &out_excess_days) const
{
    TimeSpan ts = _time_span + value;

    out_excess_days = ts.Days();
    return ts;
}

TimeOnly TimeOnly::AddHours(double hours_to_add) const
{
    double ipart;
    double fraction = std::modf( hours_to_add, &ipart );
    TimeSpan ts_whole_hours{ hours{ static_cast<int>(ipart) } };
    long fractional_hours_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerHour());

    return Add( ts_whole_hours ).Add( TimeSpan( fractional_hours_in_ticks ) );
}

TimeOnly TimeOnly::AddHours(double hours_to_add, int &out_excess_days) const
{
    using std::chrono::hours;

    TimeOnly result = AddHours( hours_to_add );
    system_clock::duration result_duration{ result._time_span };
    bool negative = ( result_duration.count() < 0);
    long h = (negative) ? std::ceil<hours>( result_duration ).count() : std::floor<hours>( result_duration ).count();
    std::ldiv_t  d = std::div( h, static_cast<long>(TimeSpan::HoursPerDay()) );

    out_excess_days = d.quot;
    return TimeSpan( result._time_span - std::chrono::days( d.quot ) );
}

TimeOnly TimeOnly::AddMinutes(double minutes) const
{
    int out_excess_minutes;

    return AddMinutes( minutes, out_excess_minutes );
}

TimeOnly TimeOnly::AddMinutes(double minutes_to_add, int &out_excess_minutes) const
{
    UNUSED(out_excess_minutes);

    double ipart;
    double fraction = std::modf( minutes_to_add, &ipart );
    TimeSpan ts_whole_minutes{ minutes{ static_cast<int>(ipart) } };
    long fractional_minutes_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerMinute());

    return Add( ts_whole_minutes ).Add( TimeSpan( fractional_minutes_in_ticks ) );
}

int TimeOnly::CompareTo(const TimeOnly &other) const
{
    auto result{ *this <=> other };

    if ( result == std::strong_ordering::less )
        return -1;
    else if ( result == std::strong_ordering::equal )
        return 0;
    else
        return 1;
}

void TimeOnly::Deconstruct(int &hour, int &minute, int &second, int &millisecond, int &microsecond) const
{
    hour = Hour();
    minute = Minute();
    second = Second();
    millisecond = Millisecond();
    microsecond = Microsecond();
}

void TimeOnly::Deconstruct(int &hour, int &minute, int &second, int &millisecond) const
{
    hour = Hour();
    minute = Minute();
    second = Second();
    millisecond = Millisecond();
}

void TimeOnly::Deconstruct(int &hour, int &minute, int &second) const
{
    hour = Hour();
    minute = Minute();
    second = Second();
}

void TimeOnly::Deconstruct(int &hour, int &minute) const
{
    hour = Hour();
    minute = Minute();
}

TimeOnly TimeOnly::FromDateTime(const System::DateTime &datetime)
{
    return TimeOnly( datetime.TimeOfDay() );
}

std::string TimeOnly::ToString() const
{
    system_clock::duration d = _time_span;
    hh_mm_ss<seconds> tod( duration_cast<seconds>(d) );

    return std::format("{}", tod);
}

}

export
template <>
struct std::formatter<System::TimeOnly>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const System::TimeOnly &object, FormatContext &ctx) const
    {
        std::chrono::system_clock::duration d = object.ToTimeSpan();
        std::chrono::hh_mm_ss<std::chrono::seconds> tod( duration_cast<std::chrono::seconds>(d) );

        return std::format_to( ctx.out(), "{}", tod);
    }
};
