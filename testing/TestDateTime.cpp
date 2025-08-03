#include "System/DateTime.hpp"
#include <iostream>
#include <cassert>


namespace TestDateTime
{

void DefaultConstruct()
{
    System::DateTime t;

    assert( t == System::DateTime().MinValue() );
}

void MinValueIsJanuaryFirstOnYearZeroAtMidnight()
{
    System::DateTime t = System::DateTime::MinValue();

    assert( t.Year() == 1 );
    assert( t.Month() == 1 );
    assert( t.Day() == 1 );
    assert( t.Hour() == 0 );
    assert( t.Minute() == 0 );
    assert( t.Second() == 0 );
}

void ConstructYearMonthDay()
{
    System::DateTime t( 1980, 1, 1 );

    assert( t.Year() == 1980 );
    assert( t.Month() == 1 );
    assert( t.Day() == 1 );
}

void ConstructYearMonthDayHourMinuteSecond()
{
    {
        System::DateTime t( 1980, 1, 1, 9, 30, 2 );

        assert( t.Year() == 1980 );
        assert( t.Month() == 1 );
        assert( t.Day() == 1 );
        assert( t.Hour() == 9 );
        assert( t.Minute() == 30 );
        assert( t.Second() == 2 );
    }
}

void DayOfWeek()
{
    System::DateTime t( 2025, 3, 6 );

    assert( t.Day() == 6 );
    assert( t.DayOfWeek() == System::DayOfWeek::Thursday );
}

void DayOfYear()
{
    assert( System::DateTime( 2025, 1, 1 ).DayOfYear() == 1 );
    assert( System::DateTime( 2025, 3, 6 ).DayOfYear() == 65 );
}

void Now()
{
    std::cout << "The time is now: " << System::DateTime::Now().ToString() << std::endl;
}

void UtcNow()
{
    std::cout << "The time is now: " << System::DateTime::UtcNow().ToString() << std::endl;
}

void Today()
{
    System::DateTime today = System::DateTime::Today();

    assert( today.Hour() == 0 );
    assert( today.Minute() == 0 );
    assert( today.Second() == 0 );
}

void Date()
{
    System::DateTime t( 2025, 3, 6, 12, 30, 30 );
    System::DateTime date = t.Date();

    // Date part
    assert( t.Year() == 2025 );
    assert( t.Month() == 3 );
    assert( t.Day() == 6 );

    // Time of day part
    assert( t.Hour() == 12 );
    assert( t.Minute() == 30 );
    assert( t.Second() == 30 );


    // Date part
    assert( date.Year() == 2025 );
    assert( date.Month() == 3 );
    assert( date.Day() == 6 );

    // Time of day part
    assert( date.Hour() == 0 );
    assert( date.Minute() == 0 );
    assert( date.Second() == 0 );
}

void Hour()
{
    System::DateTime t( 2025, 3, 6 );

    assert( t.Hour() == 0 );
}

void Minute()
{
    System::DateTime t( 2025, 3, 6, 1, 46, 33 );

    assert( t.Minute() == 46 );
}

void Second()
{
    System::DateTime t( 2025, 3, 6, 1, 46, 33 );

    assert( t.Second() == 33 );
}

void UnixEpoch()
{
    System::DateTime unix_epoch = System::DateTime::UnixEpoch();

    assert( unix_epoch.Year() == 1970 );
    assert( unix_epoch.Month() == 1 );
    assert( unix_epoch.Day() == 1 );
    assert( unix_epoch.Hour() == 0 );
    assert( unix_epoch.Minute() == 0 );
    assert( unix_epoch.Second() == 0 );
}

void OperatorEquals()
{
    System::DateTime unix_epoch = System::DateTime::UnixEpoch();
    System::DateTime unix_epoch2 = unix_epoch;
    System::DateTime now = System::DateTime::Now();

    assert( unix_epoch == unix_epoch2 );
    assert( unix_epoch != now );
}

void OperatorSpaceship()
{
    System::DateTime unix_epoch = System::DateTime::UnixEpoch();
    System::DateTime now = System::DateTime::Now();

    assert( (unix_epoch <=> now) == std::strong_ordering::less );
    assert( (now <=> now) == std::strong_ordering::equal );
    assert( (now <=> unix_epoch) == std::strong_ordering::greater );
}

void RelationalOperators()
{
    System::DateTime unix_epoch = System::DateTime::UnixEpoch();
    System::DateTime now = System::DateTime::Now();

    assert( unix_epoch < now );
    assert( now <= now );
    assert( now > unix_epoch );
    assert( now >= unix_epoch );

    assert( System::DateTime::Compare( unix_epoch, now ) == -1 );
    assert( System::DateTime::Compare( now, now ) == 0 );
    assert( System::DateTime::Compare( now, unix_epoch ) == 1 );
}

void Add()
{
    // Use only Datetime & TimeSpan
    {
        System::DateTime unix_epoch = System::DateTime::UnixEpoch();
        System::TimeSpan one_day( 1, 0 , 0, 0 );

        assert( unix_epoch.Day() == 1 );
        assert( unix_epoch.Add( one_day ).Day() == 2 );
    }
}

void AddCPlusPlusOperators()
{
    // DateTiem + TimeSpan
    {
        System::DateTime unix_epoch = System::DateTime::UnixEpoch();
        System::TimeSpan one_day( 1, 0 , 0, 0 );
        System::DateTime new_datetime = unix_epoch + one_day;

        assert( unix_epoch.Day() == 1 );
        assert( new_datetime.Day() == 2 );
    }

    // DateTime + std::chrono::system_clock::duration
    {
        System::DateTime unix_epoch = System::DateTime::UnixEpoch();
        System::DateTime new_datetime = unix_epoch + std::chrono::days(1);

        assert( unix_epoch.Day() == 1 );
        assert( new_datetime.Day() == 2 );
    }

    // DateTiem += TimeSpan
    {
        System::DateTime unix_epoch = System::DateTime::UnixEpoch();
        System::TimeSpan one_day( 1, 0 , 0, 0 );

        assert( unix_epoch.Day() == 1 );

        unix_epoch += one_day;

        assert( unix_epoch.Day() == 2 );
    }

    // DateTime += std::chrono::system_clock::duration
    {
        System::DateTime unix_epoch = System::DateTime::UnixEpoch();

        assert( unix_epoch.Day() == 1 );

        unix_epoch += std::chrono::days(1);

        assert( unix_epoch.Day() == 2 );
    }
}

void AddYears()
{
    System::DateTime unix_epoch = System::DateTime::UnixEpoch();

    // Setup
    assert( unix_epoch.Year() == 1970 );

    // Tests
    assert( unix_epoch.AddYears(1).Year() == 1971 );
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.AddYears(10).Year() == 1980 );
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.Month() == 1 ); // Original unchanged

    {
        System::DateTime new_time = unix_epoch.AddYears(2).AddMonths(2);

        assert( new_time.Year() == 1972 );
        assert( new_time.Month() == 3);
    }
    {
        System::DateTime original_time = unix_epoch.AddYears(10);

        // Setup
        assert( original_time.Year() == 1980 );

        // Tests
        assert( original_time.AddYears(-1).Year() == 1979 );
    }

    // Test for underflow of DateTime
    try
    {
        System::DateTime::MinValue().AddYears(-1);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Underflow!" << '\n';
        assert( true );
    }
    
    // Test for overflow of DateTime
    try
    {
        System::DateTime::MaxValue().AddYears(1);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Overflow!" << '\n';
        assert( true );
    }
}

void AddMonths()
{
    System::DateTime unix_epoch = System::DateTime::UnixEpoch();

    // Setup
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.Month() == 1 );

    // Tests
    assert( unix_epoch.AddMonths(10).Month() == 11 );
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.Month() == 1 ); // Original unchanged

    assert( unix_epoch.AddMonths(1).Month() == 2 );
    assert( unix_epoch.AddMonths(1).Year() == 1970 ); // Original unchanged

    {
        System::DateTime new_time = unix_epoch.AddYears(2).AddMonths(2);

        assert( new_time.Year() == 1972 );
        assert( new_time.Month() == 3);
    }
    {
        System::DateTime original_time = unix_epoch.AddYears(10);

        // Setup
        assert( original_time.Year() == 1980 );
        assert( original_time.Month() == 1 );

        // Tests
        assert( original_time.AddMonths(-1).Year() == 1979 );
        assert( original_time.AddMonths(-1).Month() == 12 );
    }

    // Test for underflow of DateTime
    try
    {
        System::DateTime::MinValue().AddMonths(-1);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Underflow!" << '\n';
        assert( true );
    }
    
    // Test for overflow of DateTime
    try
    {
        System::DateTime::MaxValue().AddMonths(1);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Overflow!" << '\n';
        assert( true );
    }

    // Test for out-of-bounds months input
    try
    {
        System::DateTime::Now().AddMonths(120'001);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Tried to add too many months over!" << '\n';
        assert( true );
    }

    try
    {
        System::DateTime::Now().AddMonths(-120'001);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Tried to add too many months under!" << '\n';
        assert( true );
    }
}

void AddDays()
{
    System::DateTime unix_epoch = System::DateTime::UnixEpoch();

    // Setup
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.Month() == 1 );
    assert( unix_epoch.Day() == 1 );

    // Tests
    assert( unix_epoch.AddDays(10).Month() == 1 );
    assert( unix_epoch.AddDays(10).Day() == 11 );
    assert( unix_epoch.AddDays(10).Year() == 1970 );
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.Month() == 1 ); // Original unchanged
    assert( unix_epoch.Day() == 1 ); // Original unchanged

    {
        System::DateTime new_time = unix_epoch.AddYears(2).AddMonths(2).AddDays(23);

        assert( new_time.Year() == 1972 );
        assert( new_time.Month() == 3);
        assert( new_time.Day() == 24 );
    }

    {
        System::DateTime original_time = unix_epoch.AddYears(10);

        // Setup
        assert( original_time.Year() == 1980 );
        assert( original_time.Month() == 1 );
        assert( original_time.Day() == 1 );

        // Tests
        assert( original_time.AddDays(-1).Year() == 1979 );
        assert( original_time.AddDays(-1).Month() == 12 );
        assert( original_time.AddDays(-1).Day() == 31 );
    }

    // Test for underflow of DateTime
    try
    {
        System::DateTime::MinValue().AddDays(-1);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Underflow!" << '\n';
        assert( true );
    }
    
    // Test for overflow of DateTime
    try
    {
        System::DateTime::MaxValue().AddDays(1);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Overflow!" << '\n';
        assert( true );
    }

    // Now to test for fractional days being added
    {
        assert( unix_epoch.Hour() == 0 );
        assert( unix_epoch.AddDays(3.5).Day() == 4 );
        assert( unix_epoch.AddDays(3.5).Hour() == 12 );
    }
}

void AddHours()
{
    System::DateTime unix_epoch = System::DateTime::UnixEpoch();

    // Setup
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.Month() == 1 );
    assert( unix_epoch.Day() == 1 );
    assert( unix_epoch.Hour() == 0 );
    // Tests
    assert( unix_epoch.AddHours(10).Hour() == 10 );
    assert( unix_epoch.AddHours(2).Hour() == 2 );
    assert( unix_epoch.AddHours(2).Year() == 1970 );
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.Month() == 1 ); // Original unchanged
    assert( unix_epoch.Day() == 1 ); // Original unchanged
    assert( unix_epoch.Hour() == 0 ); // Original unchanged

    {
        System::DateTime new_time = unix_epoch.AddYears(2).AddMonths(2).AddDays(23).AddHours(16);

        assert( new_time.Year() == 1972 );
        assert( new_time.Month() == 3);
        assert( new_time.Day() == 24 );
        assert( new_time.Hour() == 16 );
    }

    {
        System::DateTime original_time = unix_epoch.AddYears(10);

        // Setup
        assert( original_time.Year() == 1980 );
        assert( original_time.Month() == 1 );
        assert( original_time.Day() == 1 );

        // Tests
        assert( original_time.AddDays(-1).Year() == 1979 );
        assert( original_time.AddDays(-1).Month() == 12 );
        assert( original_time.AddDays(-1).Day() == 31 );
    }

    // Test for underflow of DateTime
    try
    {
        System::DateTime::MinValue().AddHours(-1);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Underflow!" << '\n';
        assert( true );
    }
    
    // Test for overflow of DateTime
    try
    {
        System::DateTime::MaxValue().AddHours(1);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Overflow!" << '\n';
        assert( true );
    }

    // Now to test for fractional Hours being added
    {
        assert( unix_epoch.Hour() == 0 );
        assert( unix_epoch.AddHours(30).Hour() == 6 );

        assert( unix_epoch.AddHours(30.5).Hour() == 6 );
        assert( unix_epoch.AddHours(30.5).Minute() == 30 );
    }
}

void SubtractingTwoDateTimesReturnsATimeSpan()
{
    // A single day...
    {
        System::TimeSpan result = System::DateTime(1980, 1, 2) - System::DateTime(1980, 1, 1);

        assert( result.Days() == 1 );
        assert( result.Hours() == 0 );
        assert( result.Minutes() == 0 );
        assert( result.Seconds() == 0 );
    }

    // A bunch of days...
    {
        System::TimeSpan result = System::DateTime(1980, 1, 31) - System::DateTime(1980, 1, 1);

        assert( result.Days() == 30 );
        assert( result.Hours() == 0 );
        assert( result.Minutes() == 0 );
        assert( result.Seconds() == 0 );
    }

    // A bunch of days BACKWARDS...
    {
        System::TimeSpan result = System::DateTime(1980, 1, 1) - System::DateTime(1980, 1, 31);

        assert( result.Days() == -30 );
        assert( result.Hours() == 0 );
        assert( result.Minutes() == 0 );
        assert( result.Seconds() == 0 );
    }

    // A single month...
    {
        System::TimeSpan result = System::DateTime(2025, 7, 5) - System::DateTime(2025, 6, 5);

        assert( result.Days() == 30 );
        assert( result.Hours() == 0 );
        assert( result.Minutes() == 0 );
        assert( result.Seconds() == 0 );
    }

    // A single month... BACKWARD
    {
        System::TimeSpan result = System::DateTime(2025, 6, 5) - System::DateTime(2025, 7, 5);

        assert( result.Days() == -30 );
        assert( result.Hours() == 0 );
        assert( result.Minutes() == 0 );
        assert( result.Seconds() == 0 );
    }

    // A single year...
    {
        System::TimeSpan result = System::DateTime(2025, 7, 5) - System::DateTime(2024, 7, 5);

        assert( result.Days() == 365 );
        assert( result.Hours() == 0 );
        assert( result.Minutes() == 0 );
        assert( result.Seconds() == 0 );
    }

    // A single year... BACKWARDS
    {
        System::TimeSpan result = System::DateTime(2024, 7, 5) - System::DateTime(2025, 7, 5);

        assert( result.Days() == -365 );
        assert( result.Hours() == 0 );
        assert( result.Minutes() == 0 );
        assert( result.Seconds() == 0 );
    }

    // Full on...
    {
        System::DateTime date1( 1996, 6, 3, 22, 15, 0 );
        System::DateTime date2( 1996, 12, 6, 13, 2, 0 );
        System::DateTime date3( 1996, 10, 12, 8, 42, 0 );

        {
            System::TimeSpan diff1 = date2 - date1;

            assert( diff1.Days() == 185 );
            assert( diff1.Hours() == 14 );
            assert( diff1.Minutes() == 47 );

            System::DateTime date4 = date3 - diff1;

            assert( date4.Year() == 1996 );
            assert( date4.Month() == 4 );
            assert( date4.Day() == 9 );
            assert( date4.Hour() == 17 );
            assert( date4.Minute() == 55 );
            assert( date4.Second() == 0 );

            System::TimeSpan diff2 = date2 - date3;

            assert( diff2.Days() == 55 );
            assert( diff2.Hours() == 4 );
            assert( diff2.Minutes() == 20 );

            System::DateTime date5 = date1 - diff2;

            assert( date5.Year() == 1996 );
            assert( date5.Month() == 4 );
            assert( date5.Day() == 9 );
            assert( date5.Hour() == 17 );
            assert( date5.Minute() == 55 );
            assert( date5.Second() == 0 );
        }
    }

}

void Run()
{
    std::cout << "Running DateTime Tests..." << std::endl;

    DefaultConstruct();
    MinValueIsJanuaryFirstOnYearZeroAtMidnight();
    ConstructYearMonthDay();
    ConstructYearMonthDayHourMinuteSecond();
    DayOfWeek();
    DayOfYear();
    Now();
    UtcNow();
    Today();
    Date();
    Hour();
    Minute();
    Second();
    UnixEpoch();
    OperatorEquals();
    OperatorSpaceship();
    RelationalOperators();
    Add();
    AddCPlusPlusOperators();
    AddYears();
    AddMonths();
    AddDays();
    AddHours();
    SubtractingTwoDateTimesReturnsATimeSpan();
}

}

int main(void)
{
    TestDateTime::Run();

    return EXIT_SUCCESS;
}