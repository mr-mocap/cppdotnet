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
}

void Run()
{
    std::cout << "Running BitConverter Tests..." << std::endl;

    GetBytesBool();
    GetBytesChar();
    GetBytesFloat();

    GetAndToAreInverses();

    std::cout << "PASSED!" << std::endl;
}

}