#include "System/TimeSpan.hpp"
#include "Utility.hpp"
#include <iostream>
#include <cassert>


namespace TestTimeSpan
{

void DefaultConstructed()
{
    System::TimeSpan t;

    assert( t.Ticks() == 0 );
    assert( t == System::TimeSpan::Zero() );
}

void DifferentConstructors()
{
    {
        System::TimeSpan t( 1, 0, 0, 0 );

        assert( t.Days() == 1 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
    }
}

void ConstructedWithDifferentDays()
{
    {
        System::TimeSpan t( 2, 0, 0, 0 );

        assert( t.Days() == 2 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
    }
    {
        System::TimeSpan t( -1, 0, 0, 0 );

        assert( t.Days() == -1 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
    }
}

void ConstructedWithDifferentHours()
{
    // We will cover some simple cases only.

    {
        System::TimeSpan t( 2, 3, 0, 0 );

        assert( t.Days() == 2 );
        assert( t.Hours() == 3 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
    }
    
    // With a negative day amount and positive hour amount
    {
        System::TimeSpan t( -1, 19, 0, 0 );

        assert( t.Days() == 0 );
        assert( t.Hours() == -5 ); // We went BACK a day & now ADD 19 hours, so -24 + 19 = -5
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
    }

    {
        System::TimeSpan t( 1, -19, 0, 0 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 5 ); // Opposite from above
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
    }

    {
        System::TimeSpan t( 0, 1, 0, 0 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 1 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
    }

    {
        System::TimeSpan t( 0, -1, 0, 0 );

        assert( t.Days() == 0 );
        assert( t.Hours() == -1 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
    }

    {
        System::TimeSpan t( 1, -1, 0, 0 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 23 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
    }

    {
        System::TimeSpan t( -1, 1, 0, 0 );

        assert( t.Days() == 0 );
        assert( t.Hours() == -23 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
    }

    {
        System::TimeSpan t( 1, 0, 0 ); // Hours, Minutes, Seconds constructor

        assert( t.Days() == 0 );
        assert( t.Hours() == 1 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );

    }
    {
        System::TimeSpan t( -1, 0, 0 ); // Hours, Minutes, Seconds constructor

        assert( t.Days() == 0 );
        assert( t.Hours() == -1 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );

    }
    {
        System::TimeSpan t( 1, -1, 0 ); // Hours, Minutes, Seconds constructor

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 59 );
        assert( t.Seconds() == 0 );

    }
    {
        System::TimeSpan t( -1, -1, 0 ); // Hours, Minutes, Seconds constructor

        assert( t.Days() == 0 );
        assert( t.Hours() == -1 );
        assert( t.Minutes() == -1 );
        assert( t.Seconds() == 0 );

    }
    {
        System::TimeSpan t( -1, 1, 0 ); // Hours, Minutes, Seconds constructor

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == -59 );
        assert( t.Seconds() == 0 );

    }
}

void ConstructedWithDifferentMinutes()
{
    // We will cover some simple cases only.

    {
        System::TimeSpan t( 0, 0, 12, 0 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 12 );
        assert( t.Seconds() == 0 );
    }

    {
        System::TimeSpan t( 0, 0, -12, 0 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == -12 );
        assert( t.Seconds() == 0 );
    }

    {
        System::TimeSpan t( 0, 0, 30, 0 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 30 );
        assert( t.Seconds() == 0 );
    }

    {
        System::TimeSpan t( 0, 0, -30, 0 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == -30 );
        assert( t.Seconds() == 0 );
    }

    {
        System::TimeSpan t( 0, 0, 1, -1 ); // Should be one minute minus one second, or 59 seconds

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 59 );
    }

    {
        System::TimeSpan t( 0, 0, -1, 1 ); // Should be one minute minus one second, or 59 seconds

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == -59 );
    }
}

void ConstructedWithDifferentSeconds()
{
    // We will cover some simple cases only.

    {
        System::TimeSpan t( 0, 0, 0, 1 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 1 );
    }
    {
        System::TimeSpan t( 0, 0, 0, -1 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == -1 );
    }
    {
        System::TimeSpan t( 0, 0, 0, 30 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 30 );
    }

    {
        System::TimeSpan t( 0, 0, 0, -30 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == -30 );
    }
}

void ConstructedWithDifferentMilliseconds()
{
    // We will cover some simple cases only.

    {
        System::TimeSpan t( 0, 0, 0, 1, 1 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 1 );
        assert( t.Milliseconds() == 1 );
    }
    {
        System::TimeSpan t( 0, 0, 0, 1, -1 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
        assert( t.Milliseconds() == 999 );
    }
    {
        System::TimeSpan t( 0, 0, 0, -1, -1 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == -1 );
        assert( t.Milliseconds() == -1 );
    }
    {
        System::TimeSpan t( 0, 0, 0, -1, 1 );

        assert( t.Days() == 0 );
        assert( t.Hours() == 0 );
        assert( t.Minutes() == 0 );
        assert( t.Seconds() == 0 );
        assert( t.Milliseconds() == -999 );
    }
}

void ConstructedWithDifferentTicks()
{
    // We will cover some simple cases only.

    {
        System::TimeSpan t( 0 );

        assert( t.Ticks() == 0 );
    }
    {
        System::TimeSpan t( 1 );

        assert( t.Ticks() == 1 );
    }
    {
        System::TimeSpan t( -1 );

        assert( t.Ticks() == -1 );
    }
}

void ConstantProperties()
{
    assert( System::TimeSpan::HoursPerDay() == 24 );
    assert( System::TimeSpan::MinutesPerDay() == 1440 );
    assert( System::TimeSpan::MinutesPerHour() == 60 );

    assert( System::TimeSpan::Zero().Days() == 0 );
    assert( System::TimeSpan::Zero().Hours() == 0 );
    assert( System::TimeSpan::Zero().Minutes() == 0 );
    assert( System::TimeSpan::Zero().Seconds() == 0 );

    assert( System::TimeSpan::MinValue().Ticks() == std::chrono::system_clock::duration::min().count() / 100 );
    assert( System::TimeSpan::MaxValue().Ticks() == std::chrono::system_clock::duration::max().count() / 100 );
}

void TotalDays()
{
    // We will cover some simple cases only.

    {
        System::TimeSpan t( 0, 0, 0, 0, 0 );

        assert( t.Days() == 0 );
        assert( t.TotalDays() == 0.0 );
    }
    {
        System::TimeSpan t( 3, 16, 42, 45, 750 );

        assert( t.Days() == 3 );
        assert( t.TotalDays() == 3.69636284722222219 );
    }
    {
        // One second worth
        System::TimeSpan t( 0, 0, 0, 1, 0 );
        double calc_ms_per_day = 1000.0 / System::TimeSpan::MillisecondsPerDay();

        assert( t.Seconds() == 1 );
        assert( t.Milliseconds() == 0 );
        assert( t.TotalDays() == calc_ms_per_day );
    }
    {
        // Half second worth
        System::TimeSpan t( 0, 0, 0, 0, 500 );
        double calc_ms_per_day = 500.0 / System::TimeSpan::MillisecondsPerDay();

        assert( t.Milliseconds() == 500 );
        assert( t.Seconds() == 0 );
        assert( t.TotalDays() == calc_ms_per_day );
    }
    {
        // One minute worth
        System::TimeSpan t( 0, 0, 1, 0, 0 );
        double calc_ms_per_day = 1.0 / System::TimeSpan::MinutesPerDay();

        assert( t.Minutes() == 1 );
        assert( t.TotalDays() == calc_ms_per_day );
    }
    {
        System::TimeSpan t( 0, 0, 0, 1, -1 );
        double calc_ms_per_day = static_cast<double>(t.Milliseconds()) / System::TimeSpan::MillisecondsPerDay();

        assert( t.Days() == 0 );
        assert( t.Milliseconds() == 999 );
        assert( t.TotalDays() == calc_ms_per_day );
    }
}

void TotalHours()
{
    // We will cover some simple cases only.

    {
        System::TimeSpan t( 0, 0, 0, 0, 0 );

        assert( t.Hours() == 0 );
        assert( t.TotalHours() == 0.0 );
    }
    {
        // One hour worth
        System::TimeSpan t( 0, 1, 0, 0, 0 );

        assert( t.Hours() == 1 );
        assert( t.TotalHours() == 1.0 );
    }
    {
        // Half hour worth
        System::TimeSpan t( 0, 0, 30, 0, 0 );
        double calc_hrs = 30.0 / System::TimeSpan::MinutesPerHour();

        assert( t.Hours() == 0.0 );
        assert( t.TotalHours() == calc_hrs );
    }
    {
        // Two hours worth
        System::TimeSpan t( 0, 2, 0, 0, 0 );

        assert( t.Hours() == 2 );
        assert( t.TotalHours() == 2.0 );
    }
    {
        // Two hours worth
        System::TimeSpan t( 0, -2, 0, 0, 0 );

        assert( t.Hours() == -2 );
        assert( t.TotalHours() == -2.0 );
    }
}

void TotalNanoseconds()
{
    // We will cover some simple cases only.

    {
        System::TimeSpan t( 0, 0, 0, 0, 0 );

        assert( t.Nanoseconds() == 0 );
        assert( t.TotalNanoseconds() == 0.0 );
    }
    {
        // One millisecond worth
        System::TimeSpan t( 0, 0, 0, 0, 1 );
        double ns_per_ms = 1'000'000;

        assert( t.Milliseconds() == 1 );
        assert( t.Nanoseconds() == ns_per_ms );
        assert( t.TotalNanoseconds() == t.Milliseconds() * ns_per_ms );
    }
    {
        // One second worth
        System::TimeSpan t( 0, 0, 0, 1, 0 );
        double calc_ns = System::TimeSpan::NanosecondsPerSecond();

        assert( t.Seconds() == 1 );
        assert( t.Nanoseconds() == 0 );
        assert( is_approximately_equal_to( t.TotalNanoseconds(), calc_ns ) );
    }
    {
        // One minute worth
        System::TimeSpan t( 0, 0, 1, 0, 0 );
        double calc_min = System::TimeSpan::NanosecondsPerSecond() * System::TimeSpan::SecondsPerMinute();

        assert( t.Minutes() == 1 );
        assert( t.Nanoseconds() == 0 );
        assert( is_approximately_equal_to( t.TotalNanoseconds(), calc_min ) );
    }
    {
        // One hour worth
        System::TimeSpan t( 0, 1, 0, 0, 0 );
        double calc_hr = System::TimeSpan::NanosecondsPerSecond() *
                         System::TimeSpan::SecondsPerMinute() *
                         System::TimeSpan::MinutesPerHour();

        assert( t.Hours() == 1 );
        assert( t.Nanoseconds() == 0 );
        assert( is_approximately_equal_to( t.TotalNanoseconds(), calc_hr ) );
    }
}

void RelationalOperators()
{
    System::TimeSpan t;

    // Equality
    {
        assert( System::TimeSpan() == System::TimeSpan::Zero() );
        assert( System::TimeSpan::MinValue() == System::TimeSpan::MinValue() );
    }

    // Less than
    {
        assert( System::TimeSpan::Zero() < System::TimeSpan( 1, 0, 0 ) );
        assert( System::TimeSpan( -12, 0, 0 ) < System::TimeSpan::Zero() );
        assert( System::TimeSpan( -2, 0, 0 ) < System::TimeSpan( -1, 0, 0 ) );
    }

    // Greater than
    {
        assert( System::TimeSpan( 1, 0, 0 ) > System::TimeSpan::Zero() );
        assert( System::TimeSpan::Zero() > System::TimeSpan( -12, 0, 0 ) );
        assert( System::TimeSpan( -1, 0, 0 ) > System::TimeSpan( -2, 0, 0 ) );
    }

    // Less than equal to
    {
        assert( System::TimeSpan::Zero() <= System::TimeSpan( 1, 0, 0 ) );
        assert( System::TimeSpan::Zero() <= System::TimeSpan::Zero() );

        assert( System::TimeSpan( -12, 0, 0 ) <= System::TimeSpan::Zero() );

        assert( System::TimeSpan( -2, 0, 0 ) <= System::TimeSpan( -2, 0, 0 ) );
    }

    // Greater than equal to
    {
        assert( System::TimeSpan( 1, 0, 0 ) >= System::TimeSpan::Zero() );
        assert( System::TimeSpan::Zero() >= System::TimeSpan( -12, 0, 0 ) );
        assert( System::TimeSpan( -1, 0, 0 ) >= System::TimeSpan( -2, 0, 0 ) );
    }
}

void PlusEqualsOperator()
{
    // Add a std::chrono::duration
    {
        System::TimeSpan t;

        assert( t.Hours() == 0 );
        assert( t.Ticks() == 0 );

        t += std::chrono::hours( 1 );

        assert( t.Hours() == 1 );
        assert( t.TotalHours() == 1 );
        assert( t.Ticks() > 0 );
    }

    // Doesn't throw exception when rolling over
    {
        System::TimeSpan t = System::TimeSpan::MaxValue();
        long ticks_before = t.Ticks();

        t += std::chrono::seconds( 1 );

        assert( t.Ticks() < ticks_before );
    }

    // Doesn't throw exception when rolling under
    {
        System::TimeSpan t = System::TimeSpan::MinValue();
        long ticks_before = t.Ticks();

        t += std::chrono::seconds( -1 );
        
        assert( t.Ticks() > ticks_before );
    }
}

void MinusEqualsOperator()
{
    // Add a std::chrono::duration
    {
        System::TimeSpan t;

        assert( t.Hours() == 0 );
        assert( t.Ticks() == 0 );

        t -= std::chrono::hours( 1 );

        assert( t.Hours() == -1 );
        assert( t.TotalHours() == -1 );
        assert( t.Ticks() < 0 );
    }

    // Doesn't throw exception when rolling over
    {
        System::TimeSpan t = System::TimeSpan::MaxValue();
        long ticks_before = t.Ticks();

        t -= std::chrono::seconds( -1 );

        assert( t.Ticks() < ticks_before );
    }

    // Doesn't throw exception when rolling under
    {
        System::TimeSpan t = System::TimeSpan::MinValue();
        long ticks_before = t.Ticks();

        t -= std::chrono::seconds( 1 );
        
        assert( t.Ticks() > ticks_before );
    }
}

void NegationOperator()
{
    {
        System::TimeSpan ts( 6 );

        assert( ts.Ticks() == 6);
        assert( (-ts).Ticks() == -6 );
    }

    {
        System::TimeSpan ts( -1000 );

        assert( ts.Ticks() == -1000);
        assert( (-ts).Ticks() == 1000 );
    }
}

void Addition()
{
    {
        System::TimeSpan ts;
        System::TimeSpan new_ts = ts + std::chrono::hours( 2 );

        assert( ts.Ticks() == 0 );
        assert( ts.Hours() == 0 );
        assert( new_ts.Hours() == 2 );
    }

    {
        System::TimeSpan ts;
        System::TimeSpan new_ts = ts + std::chrono::hours( -2 );

        assert( ts.Ticks() == 0 );
        assert( ts.Hours() == 0 );
        assert( new_ts.Hours() == -2 );
    }
}

void Subtraction()
{
    {
        System::TimeSpan ts;
        System::TimeSpan new_ts = ts - std::chrono::hours( 2 );

        assert( ts.Ticks() == 0 );
        assert( ts.Hours() == 0 );
        assert( new_ts.Hours() == -2 );
    }

    {
        System::TimeSpan ts;
        System::TimeSpan new_ts = ts - std::chrono::hours( -2 );

        assert( ts.Ticks() == 0 );
        assert( ts.Hours() == 0 );
        assert( new_ts.Hours() == 2 );
    }
}

void Multiplication()
{
    {
        System::TimeSpan ts;
        System::TimeSpan new_ts = ts * 2;

        assert( ts.Ticks() == 0 );
        assert( ts.Hours() == 0 );
        assert( new_ts.Hours() == 0 );
        assert( new_ts.Ticks() == 0 );
    }

    {
        System::TimeSpan ts;
        System::TimeSpan new_ts = ts * -2.0;

        assert( ts.Ticks() == 0 );
        assert( ts.Hours() == 0 );
        assert( new_ts.Hours() == 0 );
        assert( new_ts.Ticks() == 0 );
    }
}

void Division()
{
    {
        System::TimeSpan ts( 2, 0, 0 );
        System::TimeSpan new_ts = ts / 2;

        assert( ts.Hours() == 2 );
        assert( new_ts.Hours() == 1 );
    }
    {
        System::TimeSpan ts( 1, 0, 0 );
        System::TimeSpan new_ts = ts / 2.0;

        assert( ts.Hours() == 1 );
        assert( ts.Minutes() == 0 );
        assert( new_ts.Hours() == 0 );
        assert( new_ts.Minutes() == 30 );
    }
}

void Run()
{
    ConstantProperties();
    DefaultConstructed();
    DifferentConstructors();
    ConstructedWithDifferentDays();
    ConstructedWithDifferentHours();
    ConstructedWithDifferentMinutes();
    ConstructedWithDifferentSeconds();
    ConstructedWithDifferentMilliseconds();
    ConstructedWithDifferentTicks();
    TotalDays();
    TotalHours();
    TotalNanoseconds();
    RelationalOperators();
    PlusEqualsOperator();
    MinusEqualsOperator();
    NegationOperator();
    Addition();
    Subtraction();
    Multiplication();
    Division();
}

}

int main(void)
{
    TestTimeSpan::Run();

    return EXIT_SUCCESS;
}