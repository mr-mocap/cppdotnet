#include "TestBitConverter.hpp"
#include "System/BitConverter.hpp"
#include <iostream>
#include <cassert>

namespace TestBitConverter
{

void GetBytesBool()
{
    std::cout << __func__ << std::endl;

    std::vector<std::byte> result = System::BitConverter::GetBytes(true);

    assert( result.size() == sizeof(bool) );
    assert( std::to_integer<bool>(result[0]) == true );

    result = System::BitConverter::GetBytes(false);

    assert( result.size() == sizeof(bool) );
    assert( std::to_integer<bool>(result[0]) == false );
}

void GetBytesChar()
{
    std::cout << __func__ << std::endl;

    char input = 3;
    std::vector<std::byte> result = System::BitConverter::GetBytes(input);

    assert( result.size() == sizeof(char) );
    assert( std::to_integer<char>(result[0]) == input );

    input = -1;
    result = System::BitConverter::GetBytes(input);

    assert( result.size() == sizeof(char) );
    assert( std::to_integer<char>(result[0]) == input );
}

void GetBytesFloat()
{
    std::cout << __func__ << std::endl;

    float input = 0;
    std::vector<std::byte> result = System::BitConverter::GetBytes(input);

    assert( result.size() == sizeof(float) );
    //assert( std::to_integer<float>(result[0]) == input );

    input = -1.1;
    result = System::BitConverter::GetBytes(input);

    assert( result.size() == sizeof(float) );
    //assert( std::to_integer<float>(result[0]) == input );
}

void GetAndToAreInverses()
{
    std::cout << __func__ << std::endl;

    // Boolean
    {
        bool input = false;
        std::vector<std::byte> result = System::BitConverter::GetBytes(input);

        assert( System::BitConverter::ToBoolean(result) == input );

        input = false;
        result = System::BitConverter::GetBytes(input);

        assert( System::BitConverter::ToBoolean(result) == input );
    }

    // char
    {
        char input = 3;
        std::vector<std::byte> bytes = System::BitConverter::GetBytes(input);

        assert( System::BitConverter::ToChar(bytes) == input );

        input = -1;
        bytes = System::BitConverter::GetBytes(input);

        assert( System::BitConverter::ToChar(bytes) == input );
    }

    // float
    {
        float input = 3.14;
        std::vector<std::byte> bytes = System::BitConverter::GetBytes(input);

        assert( System::BitConverter::ToFloat(bytes) == input );

        input = -1.776;
        bytes = System::BitConverter::GetBytes(input);

        assert( System::BitConverter::ToFloat(bytes) == input );
    }
}

void ByteSwap()
{
    std::cout << __func__ << std::endl;

    // bool
    {
        bool origin = true;
        bool swapped = System::BitConverter::ByteSwap(origin);

        assert( sizeof(bool) == 1 );
        assert( origin == swapped );
    }

    // std::uint16_t
    {
        std::uint16_t origin = 0x0102;
        std::uint16_t swapped = System::BitConverter::ByteSwap(origin);

        assert( sizeof(origin) == 2 );
        assert( origin == 0x0102 );
        assert( swapped == 0x0201 );
    }

    // std::uint32_t
    {
        std::uint32_t origin = 0x01020304;
        std::uint32_t swapped = System::BitConverter::ByteSwap(origin);

        assert( sizeof(origin) == 4 );
        assert( origin == 0x01020304 );
        assert( swapped == 0x04030201 );
    }

    // std::uint64_t
    {
        std::uint64_t origin = 0x0102030405060708;
        std::uint64_t swapped = System::BitConverter::ByteSwap(origin);

        assert( sizeof(origin) == 8 );
        assert( origin == 0x0102030405060708 );
        assert( swapped == 0x0807060504030201 );
    }
}

void Run()
{
    std::cout << "Running BitConverter Tests..." << std::endl;

    GetBytesBool();
    GetBytesChar();
    GetBytesFloat();

    GetAndToAreInverses();

    ByteSwap();

    std::cout << "PASSED!" << std::endl;
}

}