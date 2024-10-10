#include "TestStringWriter.hpp"
#include "System/IO/StringWriter.hpp"
#include <iostream>
#include <cassert>

namespace TestStringWriter
{

template <class WriteType>
bool CheckWriter(WriteType input, std::string_view expected_output)
{
    System::IO::StringWriter writer;

    writer.Write( input );
    return writer.GetStringBuilder().ToString() == expected_output;
}

void DefaultConstructed()
{
    std::cout << __func__ << std::endl;

    System::IO::StringWriter writer;

    assert( writer.GetStringBuilder().Length() == 0 );
}

void VerifyWrite()
{
    using namespace std::literals;

    std::cout << __func__ << std::endl;

    CheckWriter('a', "a");
    CheckWriter("This is a string"sv, "This is a string"sv);
    CheckWriter(false, "False"sv);
    CheckWriter(true, "True"sv);
    CheckWriter(0, "0"sv); // Weird case (0 is "special")
    CheckWriter(129, "129"sv);
    CheckWriter(-328, "-328"sv);
    CheckWriter( int8_t(8), "8"sv );
    CheckWriter( int8_t(-8), "-8"sv );
    CheckWriter( int16_t(32767), "32767"sv );
    CheckWriter( int16_t(-32768), "-32768"sv );
    CheckWriter( uint16_t(65535), "65535"sv );
    CheckWriter( float(3.2), "3.2"sv );
    CheckWriter( float(-32.3), "-32.3"sv );
    CheckWriter( double(3.2), "3.2"sv );
    CheckWriter( double(-32.3), "-32.3"sv );
}

void Run()
{
    std::cout << "Running StringWriter Tests..." << std::endl;

    DefaultConstructed();
    VerifyWrite();

    std::cout << "PASSED!" << std::endl;
}

}