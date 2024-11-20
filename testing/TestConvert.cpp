#include "TestConvert.hpp"
#include "System/Convert.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>

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

void Run()
{
    std::cout << "Running Convert Tests..." << std::endl;

    FromHexString();
    ToHexString();
    ToBase64String();
    FromBase64String();

    std::cout << "PASSED!" << std::endl;
}

}