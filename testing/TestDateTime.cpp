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

void DayOfWeek()
{
    std::cout << __func__ << std::endl;

    System::DateTime t( 2025, 3, 6 );

    assert( t.Day() == 6 );
    assert( t.DayOfWeek() == System::DayOfWeek::Thursday );
}

void Now()
{
    std::cout << __func__ << std::endl;

    std::cout << "The time is now: " << System::DateTime::Now().ToString() << std::endl;
}

void Run()
{
    std::cout << "Running DateTime Tests..." << std::endl;

    ConstructYearMonthDay();
    DayOfWeek();
    Now();

    std::cout << "PASSED!" << std::endl;
}

}