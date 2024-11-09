#include "TestConvert.hpp"
#include "System/Convert.hpp"
#include <iostream>
#include <cassert>

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

void Run()
{
    std::cout << "Running Convert Tests..." << std::endl;

    FromHexString();

    std::cout << "PASSED!" << std::endl;
}

}