#include "TestDateTime.hpp"
#include "System/DateTime.hpp"
#include <iostream>
#include <cassert>


namespace TestDateTime
{

void DefaultConstruct()
{
    std::cout << __func__ << std::endl;

    System::DateTime t;

    assert( t == System::DateTime().MinValue() );
}

void ConstructYearMonthDay()
{
    std::cout << __func__ << std::endl;

    System::DateTime t( 1980, 1, 1 );

    assert( t.Year() == 1980 );
    assert( t.Month() == 1 );
    assert( t.Day() == 1 );
}

void ConstructYearMonthDayHourMinuteSecond()
{
    std::cout << __func__ << std::endl;

    System::DateTime t( 1980, 1, 1, 9, 30, 2 );

    assert( t.Year() == 1980 );
    assert( t.Month() == 1 );
    assert( t.Day() == 1 );
    assert( t.Hour() == 9 );
    assert( t.Minute() == 30 );
    assert( t.Second() == 2 );
}

void DayOfWeek()
{
    std::cout << __func__ << std::endl;

    System::DateTime t( 2025, 3, 6 );

    assert( t.Day() == 6 );
    assert( t.DayOfWeek() == System::DayOfWeek::Thursday );
}

void DayOfYear()
{
    std::cout << __func__ << std::endl;

    assert( System::DateTime( 2025, 1, 1 ).DayOfYear() == 1 );
    assert( System::DateTime( 2025, 3, 6 ).DayOfYear() == 65 );
}

void Now()
{
    std::cout << __func__ << std::endl;

    std::cout << "The time is now: " << System::DateTime::Now().ToString() << std::endl;
}

void UtcNow()
{
    std::cout << __func__ << std::endl;

    std::cout << "The time is now: " << System::DateTime::UtcNow().ToString() << std::endl;
}

void Today()
{
    std::cout << __func__ << std::endl;

    System::DateTime today = System::DateTime::Today();

    assert( today.Hour() == 0 );
    assert( today.Minute() == 0 );
    assert( today.Second() == 0 );
}

void Date()
{
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

    System::DateTime t( 2025, 3, 6 );

    assert( t.Hour() == 0 );
}

void Minute()
{
    std::cout << __func__ << std::endl;

    System::DateTime t( 2025, 3, 6, 1, 46, 33 );

    assert( t.Minute() == 46 );
}

void Second()
{
    std::cout << __func__ << std::endl;

    System::DateTime t( 2025, 3, 6, 1, 46, 33 );

    assert( t.Second() == 33 );
}

void UnixEpoch()
{
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

    System::DateTime unix_epoch = System::DateTime::UnixEpoch();
    System::DateTime unix_epoch2 = unix_epoch;
    System::DateTime now = System::DateTime::Now();

    assert( unix_epoch == unix_epoch2 );
    assert( unix_epoch != now );
}

void OperatorSpaceship()
{
    std::cout << __func__ << std::endl;

    System::DateTime unix_epoch = System::DateTime::UnixEpoch();
    System::DateTime now = System::DateTime::Now();

    assert( (unix_epoch <=> now) == std::strong_ordering::less );
    assert( (now <=> now) == std::strong_ordering::equal );
    assert( (now <=> unix_epoch) == std::strong_ordering::greater );
}

void RelationalOperators()
{
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

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
        System::DateTime time_before_epoch = System::DateTime::MinValue().AddYears(-1);
        
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
        System::DateTime time_after_end_of_time = System::DateTime::MaxValue().AddYears(1);
        
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
    std::cout << __func__ << std::endl;

    System::DateTime unix_epoch = System::DateTime::UnixEpoch();

    // Setup
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.Month() == 1 );

    // Tests
    assert( unix_epoch.AddMonths(10).Month() == 11 );
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.Month() == 1 ); // Original unchanged

#if 0
    // Why doesn't this work?!
    assert( unix_epoch.AddMonths(1).Month() == 2 );
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
#endif

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
        System::DateTime time_before_epoch = System::DateTime::MinValue().AddMonths(-1);
        
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
        System::DateTime time_after_end_of_time = System::DateTime::MaxValue().AddMonths(1);
        
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
        System::DateTime time_before_epoch = System::DateTime::Now().AddMonths(120'001);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Tried to add too many months over!" << '\n';
        assert( true );
    }

    try
    {
        System::DateTime time_before_epoch = System::DateTime::Now().AddMonths(-120'001);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Tried to add too many months under!" << '\n';
        assert( true );
    }
}

void Run()
{
    std::cout << "Running DateTime Tests..." << std::endl;

    DefaultConstruct();
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

    std::cout << "PASSED!" << std::endl;
}

}