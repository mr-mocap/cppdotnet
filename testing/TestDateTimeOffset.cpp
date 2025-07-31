#include "System/DateTimeOffset.hpp"
#include <iostream>
#include <cassert>


namespace TestDateTimeOffset
{

void ConstructWithDateTime()
{
    std::cout << __func__ << std::endl;

    System::DateTime dt( 1980, 6, 9 );

    assert( dt.Year() == 1980 );
    assert( dt.Month() == 6 );
    assert( dt.Day() == 9 );

    System::DateTimeOffset dto( dt );

    assert( dto.Year() == 1980 );
    assert( dto.Month() == 6 );
    assert( dto.Day() == 9 );

    assert( dto.DateTime() == dt );
}

void ConstructWithDateTimeAndTimeSpan()
{
    std::cout << __func__ << std::endl;

    System::DateTime dt( 1980, 6, 9 );

    assert( dt.Year() == 1980 );
    assert( dt.Month() == 6 );
    assert( dt.Day() == 9 );

    System::TimeSpan ts( 13, 45, 12 );

    assert( ts.Hours() == 13 );
    assert( ts.Minutes() == 45 );
    assert( ts.Seconds() == 12 );

    System::DateTimeOffset dto( dt, ts );

    // Test the newly constructed object
    assert( dto.Year() == 1980 );
    assert( dto.Month() == 6 );
    assert( dto.Day() == 9 );
    assert( dto.Hour() == 13 );
    assert( dto.Minute() == 45 );
    assert( dto.Second() == 12 );

    // Check that the subobjects are identical to the input of the constructor
    assert( dto.DateTime() == dt );
    assert( dto.Offset() == ts );

    std::cout << System::DateTime::MinValue().ToString() << std::endl;
}

void Run()
{
    std::cout << "Running DateTimeOffset Tests..." << std::endl;

    ConstructWithDateTime();
    ConstructWithDateTimeAndTimeSpan();
}

}

int main(void)
{
    TestDateTimeOffset::Run();

    return EXIT_SUCCESS;
}