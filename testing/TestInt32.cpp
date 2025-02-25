#include "TestInt32.hpp"
#include "System/Int32.hpp"
#include "System/Private/private.hpp"
#include <iostream>
#include <cassert>
#include <format>


namespace TestInt32
{

using namespace System;

static std::int32_t FunctionTakingStdInt32(const std::int32_t converted)
{
    std::cout << __func__ << ": converted = " << converted << std::endl;
    return converted;
}

void DefaultConstructsToZero()
{
    std::cout << __func__ << std::endl;

    Int32 a;

    assert( a == 0 );
}

void ConstructingFromAConstantInteger()
{
    std::cout << __func__ << std::endl;

    Int32 a(32);
    Int32 b{66};

    assert( a == 32 );
    assert( b == 66 );
}

void AutomaticConversionToStdInt32WhenCallingFunction()
{
    std::cout << __func__ << std::endl;

    Int32 a(17);

    assert( FunctionTakingStdInt32( a ) == 17 );
}

void GetTypeCode()
{
    std::cout << __func__ << std::endl;

    Int32 a(17);

    assert( a.GetTypeCode() == TypeCode::Int32 );
}

void ToBoolean()
{
    std::cout << __func__ << std::endl;

    {
        Int32 a(17);

        assert( a.ToBoolean() == true );
    }
    {
        Int32 a(0);

        assert( a.ToBoolean() == false );
    }
}

void ToByte()
{
    std::cout << __func__ << std::endl;

    assert( Int32{64}.ToByte() == std::byte{64} );
}

void ToChar()
{
    std::cout << __func__ << std::endl;

    assert( Int32{22}.ToChar() == char{22} );
}

void ToInt16()
{
    std::cout << __func__ << std::endl;

    assert( Int32{22}.ToInt16() == std::int16_t{22} );
    assert( Int32{32767}.ToInt16() == std::int16_t{32767} ); // Highest Value
    assert( Int32{0}.ToInt16() == std::int16_t{0} );
    assert( Int32{-1}.ToInt16() == std::int16_t{-1} );
    assert( Int32{-32768}.ToInt16() == std::int16_t{-32768} ); // Lowest Value (negative)
}

void ToInt32()
{
    std::cout << __func__ << std::endl;

    assert( Int32{22}.ToInt32() == std::int32_t{22} );
    assert( Int32{2147483647}.ToInt32() == std::int32_t{2147483647} ); // Highest Value
    assert( Int32{0}.ToInt32() == std::int32_t{0} );
    assert( Int32{-1}.ToInt32() == std::int32_t{-1} );
    assert( Int32{-2147483648}.ToInt32() == std::int32_t{-2147483648} ); // Lowest Value (negative)
}

void ToSingle()
{
    std::cout << __func__ << std::endl;

    assert( Int32{22}.ToSingle() == 22.0f );
    assert( Int32{0}.ToInt32() == 0.0f );
    assert( Int32{-1}.ToInt32() == -1.0f );
}

void ToDouble()
{
    std::cout << __func__ << std::endl;

    assert( Int32{22}.ToSingle() == 22.0 );
    assert( Int32{0}.ToInt32() == 0.0 );
    assert( Int32{-1}.ToInt32() == -1.0 );
}

void ToString()
{
    std::cout << __func__ << std::endl;

    assert( Int32{22}.ToString() == "22" );
    assert( Int32{0}.ToString() == "0" );
    assert( Int32{-1}.ToString() == "-1" );
}

void Equality()
{
    std::cout << __func__ << std::endl;

    Int32 number{65536};

    assert( number == 65536 );
    assert( 65536 == number );

    // With std::int16_t
    {
        std::int16_t int16 = 32767;

        assert( number != int16 );
        assert( int16 != number );
        assert( number != 32767 );
        assert( 32767 != number );
    }

    // With std::int8_t
    {
        std::int8_t int8 = 127;

        assert( number != int8 );
        assert( int8 != number );
        assert( number != 127 );
        assert( 127 != number );
    }
}

void TestINumberBase()
{
    std::cout << __func__ << std::endl;

    using namespace std::literals;

    assert( Int32::Zero() == 0 );
    assert( Int32::One() == 1 );

    assert( Int32::Abs(0) == 0 );
    assert( Int32::Abs(27) == 27 );
    assert( Int32::Abs(-1) == 1 );
    assert( Int32::Abs(-27) == 27 );

    assert(  Int32::IsEvenInteger(0) );
    assert( !Int32::IsEvenInteger(1) );
    assert(  Int32::IsEvenInteger(2) );
    assert( !Int32::IsEvenInteger(3) );
    assert(  Int32::IsEvenInteger(1000000) );
    assert( !Int32::IsEvenInteger(-1) );
    assert(  Int32::IsEvenInteger(-2) );

    assert(  Int32::IsNegative(-1) );
    assert( !Int32::IsNegative(0) );
    assert( !Int32::IsNegative(1) );

    assert( !Int32::IsOddInteger(0) );
    assert(  Int32::IsOddInteger(1) );
    assert( !Int32::IsOddInteger(2) );
    assert(  Int32::IsOddInteger(3) );
    assert(  Int32::IsOddInteger(-1) );
    assert( !Int32::IsOddInteger(-2) );

    assert( !Int32::IsPositive(0) );
    assert(  Int32::IsPositive(1) );
    assert( !Int32::IsPositive(-1) );

    assert(  Int32::IsZero(0) );
    assert( !Int32::IsZero(1) );
    assert( !Int32::IsZero(-1) );
}

void Parse()
{
    std::cout << __func__ << std::endl;

    using namespace std::literals;

    assert( Int32::Parse("32"sv) == 32);
    assert( Int32::Parse("32 "sv) == 32); // Trailing whitespace does not matter
    
    // Leading whitespace matters... (Not allowed)
    try
    {
        std::int32_t result = Int32::Parse(" 32"sv);

        UNUSED(result);
    }
    catch(const System::FormatException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }
    
    // Parsing an empty string...
    try
    {
        std::int32_t result = Int32::Parse(""sv);

        UNUSED(result);
    }
    catch(const System::ArgumentNullException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }
    
    // Parsing a non-integer...
    try
    {
        std::int32_t result = Int32::Parse("salad"sv);

        UNUSED(result);
    }
    catch(const System::FormatException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }
    
    // Parsing a float...
    try
    {
        // TODO: Is this proper behavior?
        std::int32_t result = Int32::Parse("3.14"sv);

        assert( result == 3 );
    }
    catch (...)
    {
        assert(false);
    }
    
    // Parsing One Greater than Int32::MaxValue()
    try
    {
        std::int64_t max = Int32::MaxValue();
        std::string  max_plus_one{ std::format("{}", max + 1) };
        std::int32_t result = Int32::Parse( max_plus_one );

        UNUSED(result);
    }
    catch(const System::OverflowException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }

    // Parsing One Less than Int32::MinValue()
    try
    {
        std::int64_t min = Int32::MinValue();
        std::string  max_plus_one{ std::format("{}", min - 1) };
        std::int32_t result = Int32::Parse( max_plus_one );

        UNUSED(result);
    }
    catch(const System::OverflowException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }
}

void TryParse()
{
    std::cout << __func__ << std::endl;

    using namespace std::literals;

    {
        auto result = Int32::TryParse("32"sv);

        assert( result.has_value() );
        assert( result.value() == 32 );
    }

    // Trailing whitespace does not matter
    {
        auto result = Int32::TryParse("32 "sv);

        assert( result );
        assert( result.has_value() );
        assert( result.value() == 32 );
    }
    
    // Leading whitespace matters... (Not allowed)
    {
        auto result = Int32::TryParse(" 32"sv);

        assert( !result );
    }
    
    // Parsing an empty string...
    {
        auto result = Int32::TryParse(""sv);

        assert( !result );
    }
    
    // Parsing a non-integer...
    {
        auto result = Int32::TryParse("salad"sv);

        assert( !result );
    }
    
    // Parsing a float...
    {
        // TODO: Is this proper behavior?
        auto result = Int32::TryParse("3.14"sv);

        // Gives us the number BEFORE the '.'
        assert( result );
        assert( result.value() == 3 );
    }
    
    // Parsing One Greater than Int32::MaxValue()
    {
        std::int64_t max = Int32::MaxValue();
        std::string  max_plus_one{ std::format("{}", max + 1) };
        auto result = Int32::TryParse( max_plus_one );

        assert( !result );
    }

    // Parsing One Less than Int32::MinValue()
    {
        std::int64_t min = Int32::MinValue();
        std::string  max_plus_one{ std::format("{}", min - 1) };
        auto result = Int32::TryParse( max_plus_one );

        assert( !result );
    }
}

void Addition()
{
    std::cout << __func__ << std::endl;

    {
        Int32 b{ 5 };
        std::int32_t result = 3 + b;

        assert( result == 8 );
    }
    {
        Int32 b{ 5 };

        assert( 5 == b );
    }
}

void Run()
{
    std::cout << "Running Int32 Tests..." << std::endl;

    DefaultConstructsToZero();
    ConstructingFromAConstantInteger();
    AutomaticConversionToStdInt32WhenCallingFunction();
    GetTypeCode();
    ToBoolean();
    ToByte();
    ToChar();
    ToInt16();
    ToInt32();
    ToSingle();
    ToDouble();
    ToString();
    Equality();
    TestINumberBase();
    Parse();
    TryParse();
    Addition();

    std::cout << "PASSED!" << std::endl;
}

}