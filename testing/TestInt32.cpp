#include "TestInt32.hpp"
#include "System/Int32.hpp"
#include <iostream>
#include <cassert>


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

    std::cout << "PASSED!" << std::endl;
}

}