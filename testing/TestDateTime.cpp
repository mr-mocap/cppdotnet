#include "TestDateTime.hpp"
#include "System/DateTime.hpp"
#include <iostream>
#include <cassert>


namespace TestDateTime
{

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
}

void Run()
{
    std::cout << "Running DateTime Tests..." << std::endl;

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

    std::cout << "PASSED!" << std::endl;
}

}