#include "System/TimeOnly.hpp"
#include <iostream>
#include <cassert>


namespace TestTimeOnly
{
    
void DefaultConstructed()
{
    System::TimeOnly t;

    assert( t == System::TimeOnly::MinValue() );
    assert( t.Hour() == 0 );
    assert( t.Minute() == 0 );
    assert( t.Second() == 0 );
    assert( t.Millisecond() == 0 );
    assert( t.Microsecond() == 0 );
    assert( t.Nanosecond() == 0 );
}

void ConstructWithDifferentHours()
{
    {
        System::TimeOnly t( 1, 0 );

        assert( t.Hour() == 1 );
        assert( t.Minute() == 0 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );
    }
    {
        System::TimeOnly t( 12, 0 );

        assert( t.Hour() == 12 );
        assert( t.Minute() == 0 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );
    }
    {
        System::TimeOnly t( 23, 0 );

        assert( t.Hour() == 23 );
        assert( t.Minute() == 0 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );
    }
    
    // Out-of-bounds hour (assert)
#if 0
    {
        System::TimeOnly t( 24, 0 );

        assert( t.Hour() == 0 );
        assert( t.Minute() == 0 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );
    }
    {
        System::TimeOnly t( -1, 0 );

        assert( t.Hour() == 0 );
        assert( t.Minute() == 0 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );
    }
#endif
}

void ConstructWithDifferentMinutes()
{
    {
        System::TimeOnly t( 0, 1 );

        assert( t.Hour() == 0 );
        assert( t.Minute() == 1 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );
    }
    {
        System::TimeOnly t( 0, 30 );

        assert( t.Hour() == 0 );
        assert( t.Minute() == 30 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );
    }
    {
        System::TimeOnly t( 0, 59 );

        assert( t.Hour() == 0 );
        assert( t.Minute() == 59 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );
    }
    
    // Out-of-bounds minute (assert)
#if 0
    {
        System::TimeOnly t( 0, 60 );

        assert( t.Hour() == 0 );
        assert( t.Minute() == 0 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );
    }
    {
        System::TimeOnly t( 0, -1 );

        assert( t.Hour() == 0 );
        assert( t.Minute() == 0 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );
    }
#endif
}

void AddHoursWithExcessDaysCaptured()
{
    {
        System::TimeOnly t( 6, 0 );

        assert( t.Hour() == 6 );
        assert( t.Minute() == 0 );
        assert( t.Second() == 0 );
        assert( t.Millisecond() == 0 );
        assert( t.Microsecond() == 0 );
        assert( t.Nanosecond() == 0 );

        int excess_days;
        System::TimeOnly sum = t.Add( System::TimeSpan( 20, 0, 0 ), excess_days );

        assert( excess_days == 1 );
        assert( sum.Hour() == 2 );
    }
}

void Run()
{
    DefaultConstructed();
    ConstructWithDifferentHours();
    ConstructWithDifferentMinutes();
    AddHoursWithExcessDaysCaptured();
}

}

int main(void)
{
    TestTimeOnly::Run();

    return EXIT_SUCCESS;
}