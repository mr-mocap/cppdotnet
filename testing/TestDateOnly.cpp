#include <cppdotnet/System/DateOnly.hpp>
#include <cppdotnet/System/DateTime.hpp>
#include <iostream>
#include <cassert>


namespace TestDateOnly
{

void MinValueIsJanuaryFirstOnYearZeroAtMidnight()
{
    System::DateOnly t{ System::DateOnly::MinValue() };

    assert( t.Year() == 1 );
    assert( t.Month() == 1 );
    assert( t.Day() == 1 );
}

void MaxValueIsTheLastDayOfYear9999()
{
    System::DateOnly t{ System::DateOnly::MaxValue() };

    assert( t.Year() == 9999 );
    assert( t.Month() == 12 );
    assert( t.Day() == 31 );
}

void ConstructYearMonthDay()
{
    {
        System::DateOnly t( 1980, 3, 14 );

        assert( t.Year() == 1980 );
        assert( t.Month() == 3 );
        assert( t.Day() == 14 );
    }
}

void DayOfWeek()
{
    {
        System::DateOnly t( 2025, 3, 6 );

        assert( t.Day() == 6 );
        assert( t.DayOfWeek() == System::DayOfWeek::Thursday );
    }
    {
        System::DateOnly t( 2025, 3, 7 );

        assert( t.Day() == 7 );
        assert( t.DayOfWeek() == System::DayOfWeek::Friday );
    }
    {
        System::DateOnly t( 2025, 3, 8 );

        assert( t.Day() == 8 );
        assert( t.DayOfWeek() == System::DayOfWeek::Saturday );
    }
    {
        System::DateOnly t( 2025, 3, 9 );

        assert( t.Day() == 9 );
        assert( t.DayOfWeek() == System::DayOfWeek::Sunday );
    }
    {
        System::DateOnly t( 2025, 3, 10 );

        assert( t.Day() == 10 );
        assert( t.DayOfWeek() == System::DayOfWeek::Monday );
    }
    {
        System::DateOnly t( 2025, 3, 11 );

        assert( t.Day() == 11 );
        assert( t.DayOfWeek() == System::DayOfWeek::Tuesday );
    }
    {
        System::DateOnly t( 2025, 3, 12 );

        assert( t.Day() == 12 );
        assert( t.DayOfWeek() == System::DayOfWeek::Wednesday );
    }
}

void DayOfYear()
{
    assert( System::DateOnly( 2025, 1, 1 ).DayOfYear() == 1 );
    
    // Jan - 31 days, Feb - 28 days, Mar - 6 days
    assert( System::DateOnly( 2025, 3, 6 ).DayOfYear() == (31 + 28 + 6) );
}

void OperatorEquals()
{
    System::DateOnly first_date( 1929, 6, 9);
    System::DateOnly second_date( 1929, 6, 9 );
    System::DateOnly third_date( 2011, 9, 11 );
    
    assert( first_date == second_date );
    assert( second_date == first_date );
    assert( first_date != third_date );
    assert( third_date != first_date );
    assert( first_date.Equals( second_date ) );
    assert( second_date.Equals( first_date ) );
    assert( !first_date.Equals( third_date ) );
}

void OperatorSpaceship()
{
    System::DateOnly first_date( 1980, 1, 1);
    System::DateOnly second_date( 1990, 6, 9 );
    
    assert( (first_date <=> second_date) == std::strong_ordering::less );
    assert( (second_date <=> second_date) == std::strong_ordering::equal );
    assert( (second_date <=> first_date) == std::strong_ordering::greater );
}

void RelationalOperators()
{
    System::DateOnly unix_epoch(1970, 1, 1);
    System::DateOnly now(2025, 3, 19);

    assert( unix_epoch < now );
    assert( now <= now );
    assert( now > unix_epoch );
    assert( now >= unix_epoch );

    assert( unix_epoch.CompareTo( now ) == -1 );
    assert( now.CompareTo( now ) == 0 );
    assert( now.CompareTo( unix_epoch ) == 1 );
}

void AddYears()
{
    System::DateOnly unix_epoch(1970, 1, 1);

    // Setup
    assert( unix_epoch.Year() == 1970 );

    // Tests
    assert( unix_epoch.AddYears(1).Year() == 1971 );
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.AddYears(10).Year() == 1980 );
    assert( unix_epoch.Year() == 1970 ); // Original unchanged
    assert( unix_epoch.Month() == 1 ); // Original unchanged

    {
        System::DateOnly new_time = unix_epoch.AddYears(2).AddMonths(2);

        assert( new_time.Year() == 1972 );
        assert( new_time.Month() == 3);
    }
    {
        System::DateOnly original_time = unix_epoch.AddYears(10);

        // Setup
        assert( original_time.Year() == 1980 );

        // Tests
        assert( original_time.AddYears(-1).Year() == 1979 );
    }
#if 0
    // Test for underflow of DateTime
    try
    {
        System::DateOnly::MinValue().AddYears(-1);
        
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
#endif
}

void AddMonths()
{
    System::DateOnly unix_epoch(1970, 1, 1);

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
        System::DateOnly new_time = unix_epoch.AddYears(2).AddMonths(2);

        assert( new_time.Year() == 1972 );
        assert( new_time.Month() == 3);
    }
    {
        System::DateOnly original_time = unix_epoch.AddYears(10);

        // Setup
        assert( original_time.Year() == 1980 );
        assert( original_time.Month() == 1 );

        // Tests
        assert( original_time.AddMonths(-1).Year() == 1979 );
        assert( original_time.AddMonths(-1).Month() == 12 );
    }
#if 0
    // Test for underflow of DateTime
    try
    {
        System::DateOnly::MinValue().AddMonths(-1);
        
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
        System::DateOnly::MaxValue().AddMonths(1);
        
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
        System::DateOnly::Now().AddMonths(120'001);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Tried to add too many months over!" << '\n';
        assert( true );
    }

    try
    {
        System::DateOnly::Now().AddMonths(-120'001);
        
        assert( false );
    }
    catch(const System::ArgumentOutOfRangeException &e)
    {
        std::cerr << "Tried to add too many months under!" << '\n';
        assert( true );
    }
#endif
}

void AddDays()
{
    System::DateOnly unix_epoch(1970, 1, 1);

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
        System::DateOnly new_time = unix_epoch.AddYears(2).AddMonths(2).AddDays(23);

        assert( new_time.Year() == 1972 );
        assert( new_time.Month() == 3);
        assert( new_time.Day() == 24 );
    }

    {
        System::DateOnly original_time = unix_epoch.AddYears(10);

        // Setup
        assert( original_time.Year() == 1980 );
        assert( original_time.Month() == 1 );
        assert( original_time.Day() == 1 );

        // Tests
        assert( original_time.AddDays(-1).Year() == 1979 );
        assert( original_time.AddDays(-1).Month() == 12 );
        assert( original_time.AddDays(-1).Day() == 31 );
    }
#if 0
    // Test for underflow of DateTime
    try
    {
        System::DateOnly::MinValue().AddDays(-1);
        
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
        System::DateOnly::MaxValue().AddDays(1);
        
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
#endif
}

void FromDateTime()
{
    System::DateTime dt(1999, 12, 31);
    System::DateOnly t = System::DateOnly::FromDateTime( dt );

    assert( t.Year() == 1999 );
    assert( t.Month() == 12 );
    assert( t.Day() == 31 );
}

void Deconstruct()
{
    System::DateOnly dateonly(1949, 8, 4);
    int y = 0;
    int m = 0;
    int d = 0;

    assert( y == 0 );
    assert( m == 0 );
    assert( d == 0 );

    dateonly.Deconstruct( y, m, d );

    assert( y == 1949 );
    assert( m == 8 );
    assert( d == 4 );
}

void ToString()
{
    System::DateOnly dateonly(1949, 8, 4);

    std::cout << dateonly.ToString() << std::endl;
}

void Run()
{
    MinValueIsJanuaryFirstOnYearZeroAtMidnight();
    MaxValueIsTheLastDayOfYear9999();
    ConstructYearMonthDay();
    DayOfWeek();
    DayOfYear();
    OperatorEquals();
    OperatorSpaceship();
    RelationalOperators();
    AddYears();
    AddMonths();
    AddDays();
    FromDateTime();
    Deconstruct();
    ToString();
}

}

int main(void)
{
    TestDateOnly::Run();

    return EXIT_SUCCESS;
}