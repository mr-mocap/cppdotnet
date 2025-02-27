#include "TestConvert.hpp"
#include "System/Convert.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <limits>

namespace TestConvert
{

void FromHexString()
{
    std::cout << __func__ << std::endl;

    // Single byte string
    {
        std::vector<std::byte> fromhex{ System::Convert::FromHexString("00") };

        assert( fromhex.size() == 1 );
        assert( fromhex[0] == static_cast<std::byte>(0) );
    }

    {
        std::vector<std::byte> fromhex{ System::Convert::FromHexString("0A") };

        assert( fromhex.size() == 1 );
        assert( fromhex[0] == static_cast<std::byte>(10) );
    }

    {
        std::vector<std::byte> fromhex{ System::Convert::FromHexString("A0") };

        assert( fromhex.size() == 1 );
        assert( fromhex[0] == static_cast<std::byte>(160) );
    }

    // Two-bytes
    {
        std::vector<std::byte> fromhex{ System::Convert::FromHexString("FFFF") };

        assert( fromhex.size() == 2 );
        assert( fromhex[0] == static_cast<std::byte>(255) );
        assert( fromhex[1] == static_cast<std::byte>(255) );
    }

    // A bunch of bytes (low nybble)
    {
        std::vector<std::byte> fromhex{ System::Convert::FromHexString("000102030405060708090A0B0C0D0E0F") };

        assert( fromhex.size() == 16 );
        assert( fromhex[0] == static_cast<std::byte>(0) );
        assert( fromhex[1] == static_cast<std::byte>(1) );
        assert( fromhex[2] == static_cast<std::byte>(2) );
        assert( fromhex[3] == static_cast<std::byte>(3) );
        assert( fromhex[4] == static_cast<std::byte>(4) );
        assert( fromhex[5] == static_cast<std::byte>(5) );
        assert( fromhex[6] == static_cast<std::byte>(6) );
        assert( fromhex[7] == static_cast<std::byte>(7) );
        assert( fromhex[8] == static_cast<std::byte>(8) );
        assert( fromhex[9] == static_cast<std::byte>(9) );
        assert( fromhex[10] == static_cast<std::byte>(10) );
        assert( fromhex[11] == static_cast<std::byte>(11) );
        assert( fromhex[12] == static_cast<std::byte>(12) );
        assert( fromhex[13] == static_cast<std::byte>(13) );
        assert( fromhex[14] == static_cast<std::byte>(14) );
        assert( fromhex[15] == static_cast<std::byte>(15) );
    }

    // A bunch of bytes (high nybble)
    {
        std::vector<std::byte> fromhex{ System::Convert::FromHexString("00102030405060708090A0B0C0D0E0F0") };

        assert( fromhex.size() == 16 );
        assert( fromhex[0] == static_cast<std::byte>(0 * 16) );
        assert( fromhex[1] == static_cast<std::byte>(1 * 16) );
        assert( fromhex[2] == static_cast<std::byte>(2 * 16) );
        assert( fromhex[3] == static_cast<std::byte>(3 * 16) );
        assert( fromhex[4] == static_cast<std::byte>(4 * 16) );
        assert( fromhex[5] == static_cast<std::byte>(5 * 16) );
        assert( fromhex[6] == static_cast<std::byte>(6 * 16) );
        assert( fromhex[7] == static_cast<std::byte>(7 * 16) );
        assert( fromhex[8] == static_cast<std::byte>(8 * 16) );
        assert( fromhex[9] == static_cast<std::byte>(9 * 16) );
        assert( fromhex[10] == static_cast<std::byte>(10 * 16) );
        assert( fromhex[11] == static_cast<std::byte>(11 * 16) );
        assert( fromhex[12] == static_cast<std::byte>(12 * 16) );
        assert( fromhex[13] == static_cast<std::byte>(13 * 16) );
        assert( fromhex[14] == static_cast<std::byte>(14 * 16) );
        assert( fromhex[15] == static_cast<std::byte>(15 * 16) );
    }
}

void ToHexString()
{
    std::cout << __func__ << std::endl;

    // Single byte string ()
    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{0} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "00" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{1} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "01" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{2} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "02" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{3} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "03" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{4} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "04" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{5} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "05" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{6} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "06" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{7} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "07" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{8} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "08" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{9} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "09" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{10} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "0A" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{11} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "0B" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{12} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "0C" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{13} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "0D" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{14} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "0E" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{15} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "0F" );
    }

    // Upper-Nybble
    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 1} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "10" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 2} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "20" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 3} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "30" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 4} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "40" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 5} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "50" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 6} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "60" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 7} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "70" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 8} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "80" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 9} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "90" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 10} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "A0" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 11} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "B0" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 12} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "C0" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 13} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "D0" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 14} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "E0" );
    }

    {
        std::string tohex{ System::Convert::ToHexString( { std::byte{16 * 15} } ) };

        assert( tohex.size() == 2 );
        assert( tohex == "F0" );
    }
}

void ToBase64String()
{
    std::cout << __func__ << std::endl;

    {
        std::string tohex{ System::Convert::ToBase64String( "Man" ) };

        assert( tohex.size() == 4 );
        assert( tohex == "TWFu" );
    }

    {
        std::string tohex{ System::Convert::ToBase64String( "Ma" ) };

        assert( tohex.size() == 4 );
        assert( tohex == "TWE=" );
    }

    {
        std::string tohex{ System::Convert::ToBase64String( "M" ) };

        assert( tohex.size() == 4 );
        assert( tohex == "TQ==" );
    }

    {
        std::vector<uint8_t> bytes{ 0x4D, 0x61, 0x6e };
        std::string tohex{ System::Convert::ToBase64String( std::as_bytes( std::span(bytes) ) ) };

        assert( tohex.size() == 4 );
        assert( tohex == "TWFu" );
    }
}

void FromBase64String()
{
    std::cout << __func__ << std::endl;

    {
        std::vector<std::byte> original{ System::Convert::FromBase64String("TWFu") };
        std::string converted;

        std::ranges::transform(original, std::back_inserter(converted), std::to_integer<char>);
        assert( converted == "Man" );
    }
    {
        std::vector<std::byte> original{ System::Convert::FromBase64String("TWE=") };
        std::string converted;

        std::ranges::transform(original, std::back_inserter(converted), std::to_integer<char>);
        assert( converted == "Ma" );
    }
    {
        std::vector<std::byte> original{ System::Convert::FromBase64String("TQ==") };
        std::string converted;

        std::ranges::transform(original, std::back_inserter(converted), std::to_integer<char>);
        assert( converted == "M" );
    }
}

void FromBase64StringAndToBase64StringAreInverses()
{
    std::cout << __func__ << std::endl;

}

void ToBase85String()
{
    std::cout << __func__ << std::endl;

    // Various 4-byte sequences
    {
        std::string str{ "hewk" };
        std::span str_span{ str.data(), str.size() };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( str_span ) ) };

        assert( base85_string.size() == 5 );
        assert( base85_string == "BOuC'" );
    }
    {
        std::string str{ "what" };
        std::span str_span{ str.data(), str.size() };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( str_span ) ) };

        assert( base85_string.size() == 5 );
        assert( base85_string == "GA(E," );
    }
    {
        std::string str{ "Lots" };
        std::span str_span{ str.data(), str.size() };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( str_span ) ) };

        assert( base85_string.size() == 5 );
        assert( base85_string == "9Q,#o" );
    }

    // 4 zeros
    {
        std::array<const std::byte, 4> bytes{ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0} };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( std::span{ bytes } ) ) };

        assert( base85_string.size() == 1 );
        assert( base85_string == "z" );
    }

    // 4 spaces
    {
        std::array<const std::byte, 4> bytes{ std::byte{0x20}, std::byte{0x20}, std::byte{0x20}, std::byte{0x20} };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( std::span{ bytes } ) ) };

        assert( base85_string.size() == 1 );
        assert( base85_string == "y" );
    }

    // 1-byte sequences
    {
        std::string str{ "a" };
        std::span str_span{ str.data(), str.size() };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( str_span ) ) };

        assert( base85_string.size() == 2 );
        assert( base85_string == "@/" );
    }
    {
        std::string str{ "b" };
        std::span str_span{ str.data(), str.size() };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( str_span ) ) };

        assert( base85_string.size() == 2 );
        assert( base85_string == "@K" );
    }
    {
        std::string str{ "c" };
        std::span str_span{ str.data(), str.size() };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( str_span ) ) };

        assert( base85_string.size() == 2 );
        assert( base85_string == "@f" );
    }
    {
        std::string str{ "d" };
        std::span str_span{ str.data(), str.size() };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( str_span ) ) };

        assert( base85_string.size() == 2 );
        assert( base85_string == "A," );
    }

    // 2-byte sequences
    {
        std::string str{ "qq" };
        std::span str_span{ str.data(), str.size() };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( str_span ) ) };

        assert( base85_string.size() == 3 );
        assert( base85_string == "EH(" );
    }

    // 3-byte sequences
    {
        std::string str{ "abc" };
        std::span str_span{ str.data(), str.size() };
        std::string base85_string{ System::Convert::ToBase85String( std::as_bytes( str_span ) ) };

        assert( base85_string.size() == 4 );
        assert( base85_string == "@:E^" );
    }
}

void ToBase()
{
    std::cout << __func__ << std::endl;

    {
        System::Convert::BaseConversion32Bit_t result  = System::Convert::ToBase(3, 2);

        assert( result.base == 2 );
        assert( result.number_of_digits == 2 );
        assert( result.output_digits[0] == std::byte(1) );
        assert( result.output_digits[1] == std::byte(1) );
    }
    {
        System::Convert::BaseConversion32Bit_t result = System::Convert::ToBase(4, 2);

        assert( result.base == 2 );
        assert( result.number_of_digits == 3 );
        assert( result.output_digits[0] == std::byte(0) );
        assert( result.output_digits[1] == std::byte(0) );
        assert( result.output_digits[2] == std::byte(1) );
    }
    { // Minimum Value
        System::Convert::BaseConversion32Bit_t result = System::Convert::ToBase(0, 2);

        assert( result.base == 2 );
        assert( result.number_of_digits == 1 );
        assert( result.output_digits[0] == std::byte(0) );
    }
    { // Maximum Value
        System::Convert::BaseConversion32Bit_t result = System::Convert::ToBase(std::numeric_limits<std::uint32_t>::max(), 2);

        assert( result.base == 2 );
        assert( result.number_of_digits == 32 );
        assert( result.output_digits[0] == std::byte(1) );
        assert( result.output_digits[1] == std::byte(1) );
        assert( result.output_digits[2] == std::byte(1) );
        assert( result.output_digits[3] == std::byte(1) );
        assert( result.output_digits[4] == std::byte(1) );
        assert( result.output_digits[5] == std::byte(1) );
        assert( result.output_digits[6] == std::byte(1) );
        assert( result.output_digits[7] == std::byte(1) );
        assert( result.output_digits[8] == std::byte(1) );
        assert( result.output_digits[9] == std::byte(1) );
        assert( result.output_digits[10] == std::byte(1) );
        assert( result.output_digits[11] == std::byte(1) );
        assert( result.output_digits[12] == std::byte(1) );
        assert( result.output_digits[13] == std::byte(1) );
        assert( result.output_digits[14] == std::byte(1) );
        assert( result.output_digits[15] == std::byte(1) );
        assert( result.output_digits[16] == std::byte(1) );
        assert( result.output_digits[17] == std::byte(1) );
        assert( result.output_digits[18] == std::byte(1) );
        assert( result.output_digits[19] == std::byte(1) );
        assert( result.output_digits[20] == std::byte(1) );
        assert( result.output_digits[21] == std::byte(1) );
        assert( result.output_digits[22] == std::byte(1) );
        assert( result.output_digits[23] == std::byte(1) );
        assert( result.output_digits[24] == std::byte(1) );
        assert( result.output_digits[25] == std::byte(1) );
        assert( result.output_digits[26] == std::byte(1) );
        assert( result.output_digits[27] == std::byte(1) );
        assert( result.output_digits[28] == std::byte(1) );
        assert( result.output_digits[29] == std::byte(1) );
        assert( result.output_digits[30] == std::byte(1) );
        assert( result.output_digits[31] == std::byte(1) );
    }
}

void Run()
{
    std::cout << "Running Convert Tests..." << std::endl;

    FromHexString();
    ToHexString();
    ToBase64String();
    FromBase64String();
    ToBase85String();
    ToBase();

    std::cout << "PASSED!" << std::endl;
}

}