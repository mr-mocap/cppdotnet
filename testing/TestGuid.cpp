#include "TestGuid.hpp"
#include "System/Guid.hpp"
#include <cassert>
#include <iostream>
#include <ranges>


namespace TestGuid
{

static unsigned char AllZeroBits[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char AllOneBits[16] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

void ConstructWithSpanOfBytes()
{
    std::cout << __func__ << std::endl;

    // All 0's
    {
        System::Guid guid( std::as_bytes( std::span(AllZeroBits) ) );
        System::ReadOnlySpan<std::byte, 16> converted_to_array = guid.ToByteArray();

        // Compare with AllZeroBits array...
        for (size_t i : std::ranges::iota_view{ 0U, converted_to_array.Length() - 1 })
            assert( converted_to_array[i] == std::byte{AllZeroBits[i]} );
    }

    // All 255's
    {
        System::Guid guid( std::as_bytes( std::span(AllOneBits) ) );
        System::ReadOnlySpan<std::byte, 16> converted_to_array = guid.ToByteArray();

        // Compare with AllOneBits array...
        for (size_t i : std::ranges::iota_view{ 0U, converted_to_array.Length() - 1 })
            assert( converted_to_array[i] == std::byte{AllOneBits[i]} );
    }
}

void ConstructWithNFormatString()
{
    std::cout << __func__ << std::endl;

    System::Guid guid("7e44885fb76d4c05a6f2460a803d8f28");

    System::ReadOnlySpan<std::byte, 16> bytes = guid.ToByteArray();

    // Use the hex string values, but without the hyphens...
    assert( bytes[0] == std::byte{0x7e} );
    assert( bytes[1] == std::byte{0x44} );
    assert( bytes[2] == std::byte{0x88} );
    assert( bytes[3] == std::byte{0x5f} );

    assert( bytes[4] == std::byte{0xb7} );
    assert( bytes[5] == std::byte{0x6d} );

    assert( bytes[6] == std::byte{0x4c} );
    assert( bytes[7] == std::byte{0x05} );

    assert( bytes[8] == std::byte{0xa6} );
    assert( bytes[9] == std::byte{0xf2} );

    assert( bytes[10] == std::byte{0x46} );
    assert( bytes[11] == std::byte{0x0a} );
    assert( bytes[12] == std::byte{0x80} );
    assert( bytes[13] == std::byte{0x3d} );
    assert( bytes[14] == std::byte{0x8f} );
    assert( bytes[15] == std::byte{0x28} );
}

void ConstructWithDFormatString()
{
    std::cout << __func__ << std::endl;

    System::Guid object( "7e44885f-b76d-4c05-a6f2-460a803d8f28" );
    System::ReadOnlySpan<std::byte, 16> bytes = object.ToByteArray();

    // Use the hex string values, but without the hyphens...
    assert( bytes[0] == std::byte{0x7e} );
    assert( bytes[1] == std::byte{0x44} );
    assert( bytes[2] == std::byte{0x88} );
    assert( bytes[3] == std::byte{0x5f} );

    assert( bytes[4] == std::byte{0xb7} );
    assert( bytes[5] == std::byte{0x6d} );

    assert( bytes[6] == std::byte{0x4c} );
    assert( bytes[7] == std::byte{0x05} );

    assert( bytes[8] == std::byte{0xa6} );
    assert( bytes[9] == std::byte{0xf2} );

    assert( bytes[10] == std::byte{0x46} );
    assert( bytes[11] == std::byte{0x0a} );
    assert( bytes[12] == std::byte{0x80} );
    assert( bytes[13] == std::byte{0x3d} );
    assert( bytes[14] == std::byte{0x8f} );
    assert( bytes[15] == std::byte{0x28} );
}

void ConstructWithBFormatString()
{
    std::cout << __func__ << std::endl;

    System::Guid object( "{7e44885f-b76d-4c05-a6f2-460a803d8f28}" );
    System::ReadOnlySpan<std::byte, 16> bytes = object.ToByteArray();

    // Use the hex string values, but without the hyphens...
    assert( bytes[0] == std::byte{0x7e} );
    assert( bytes[1] == std::byte{0x44} );
    assert( bytes[2] == std::byte{0x88} );
    assert( bytes[3] == std::byte{0x5f} );

    assert( bytes[4] == std::byte{0xb7} );
    assert( bytes[5] == std::byte{0x6d} );

    assert( bytes[6] == std::byte{0x4c} );
    assert( bytes[7] == std::byte{0x05} );

    assert( bytes[8] == std::byte{0xa6} );
    assert( bytes[9] == std::byte{0xf2} );

    assert( bytes[10] == std::byte{0x46} );
    assert( bytes[11] == std::byte{0x0a} );
    assert( bytes[12] == std::byte{0x80} );
    assert( bytes[13] == std::byte{0x3d} );
    assert( bytes[14] == std::byte{0x8f} );
    assert( bytes[15] == std::byte{0x28} );
}

void ConstructWithPFormatString()
{
    std::cout << __func__ << std::endl;

    System::Guid object = System::Guid::Parse( "(7e44885f-b76d-4c05-a6f2-460a803d8f28)" );
    System::ReadOnlySpan<std::byte, 16> bytes = object.ToByteArray();

    // Use the hex string values, but without the hyphens...
    assert( bytes[0] == std::byte{0x7e} );
    assert( bytes[1] == std::byte{0x44} );
    assert( bytes[2] == std::byte{0x88} );
    assert( bytes[3] == std::byte{0x5f} );

    assert( bytes[4] == std::byte{0xb7} );
    assert( bytes[5] == std::byte{0x6d} );

    assert( bytes[6] == std::byte{0x4c} );
    assert( bytes[7] == std::byte{0x05} );

    assert( bytes[8] == std::byte{0xa6} );
    assert( bytes[9] == std::byte{0xf2} );

    assert( bytes[10] == std::byte{0x46} );
    assert( bytes[11] == std::byte{0x0a} );
    assert( bytes[12] == std::byte{0x80} );
    assert( bytes[13] == std::byte{0x3d} );
    assert( bytes[14] == std::byte{0x8f} );
    assert( bytes[15] == std::byte{0x28} );
}

void ConstructWithXFormatString()
{
    std::cout << __func__ << std::endl;

    System::Guid object = System::Guid::Parse( "{0x7e44885f,0xb76d,0x4c05,{0xa6,0xf2,0x46,0x0a,0x80,0x3d,0x8f,0x28}}" );
    System::ReadOnlySpan<std::byte, 16> bytes = object.ToByteArray();

    // Use the hex string values, but without the hyphens...
    assert( bytes[0] == std::byte{0x7e} );
    assert( bytes[1] == std::byte{0x44} );
    assert( bytes[2] == std::byte{0x88} );
    assert( bytes[3] == std::byte{0x5f} );

    assert( bytes[4] == std::byte{0xb7} );
    assert( bytes[5] == std::byte{0x6d} );

    assert( bytes[6] == std::byte{0x4c} );
    assert( bytes[7] == std::byte{0x05} );

    assert( bytes[8] == std::byte{0xa6} );
    assert( bytes[9] == std::byte{0xf2} );

    assert( bytes[10] == std::byte{0x46} );
    assert( bytes[11] == std::byte{0x0a} );
    assert( bytes[12] == std::byte{0x80} );
    assert( bytes[13] == std::byte{0x3d} );
    assert( bytes[14] == std::byte{0x8f} );
    assert( bytes[15] == std::byte{0x28} );
}

void EmptyProducesAllZeros()
{
    std::cout << __func__ << std::endl;

    System::Guid empty = System::Guid::Empty();
    System::ReadOnlySpan<std::byte, 16> converted_to_array = empty.ToByteArray();

    // Compare with AllZeroBits array...
    for (size_t i : std::ranges::iota_view{ 0U, converted_to_array.Length() - 1 })
        assert( converted_to_array[i] == std::byte{AllZeroBits[i]} );
}

void AllBitsSetProducesAllBitsSet()
{
    std::cout << __func__ << std::endl;

    System::Guid all_bits_set = System::Guid::AllBitsSet();
    System::ReadOnlySpan<std::byte, 16> converted_to_array = all_bits_set.ToByteArray();

    // Compare with AllOneBits array...
    for (size_t i : std::ranges::iota_view{ 0U, converted_to_array.Length() - 1 })
        assert( converted_to_array[i] == std::byte{AllOneBits[i]} );
}

void ToArrayReturnsUnderlyingValues()
{
    std::cout << __func__ << std::endl;

    unsigned char init_array[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    System::Guid guid( std::as_bytes( std::span(init_array) ) );
    System::ReadOnlySpan<std::byte, 16> converted_to_array = guid.ToByteArray();

    // Compare with array...
    for (size_t i : std::ranges::iota_view{ 0U, converted_to_array.Length() - 1 })
        assert( converted_to_array[i] == std::byte{init_array[i]} );
}

void ToStringNoParameter()
{
    std::cout << __func__ << std::endl;

    std::string s = System::Guid::NewGuid().ToString();

    std::cout << s << std::endl;

    assert( s.size() == 36 );
    assert( s[8] == '-' );
    assert( s[13] == '-' );
    assert( s[18] == '-' );
    assert( s[23] == '-' );
}

void ToStringNParameter()
{
    std::cout << __func__ << std::endl;

    std::string s = System::Guid::NewGuid().ToString("N");

    std::cout << s << std::endl;

    assert( s.size() == 32 );
    assert( s.find('-') == std::string::npos ); // No hyphen!
}

void ToStringDParameter()
{
    // Same as no parameter
    std::cout << __func__ << std::endl;

    std::string s = System::Guid::NewGuid().ToString();

    std::cout << s << std::endl;

    assert( s.size() == 36 );
    assert( s[8] == '-' );
    assert( s[13] == '-' );
    assert( s[18] == '-' );
    assert( s[23] == '-' );
}

void ToStringBParameter()
{
    // Same as no parameter
    std::cout << __func__ << std::endl;

    std::string s = System::Guid::NewGuid().ToString("B");

    std::cout << s << std::endl;

    assert( s.size() == 38 );
    assert( s.front() == '{' );
    assert( s.back() == '}' );
    assert( s[9] == '-' );
    assert( s[14] == '-' );
    assert( s[19] == '-' );
    assert( s[24] == '-' );
}

void ToStringPParameter()
{
    // Same as no parameter
    std::cout << __func__ << std::endl;

    std::string s = System::Guid::NewGuid().ToString("P");

    std::cout << s << std::endl;

    assert( s.size() == 38 );
    assert( s.front() == '(' );
    assert( s.back() == ')' );
    assert( s[9] == '-' );
    assert( s[14] == '-' );
    assert( s[19] == '-' );
    assert( s[24] == '-' );
}

void ToStringXParameter()
{
    // Same as no parameter
    std::cout << __func__ << std::endl;

    std::string s = System::Guid::NewGuid().ToString("X");

    std::cout << s << std::endl;

    assert( s.size() == 68 );

    // Brace locations...
    assert( s.front() == '{' );
    assert( s.back() == '}' );
    assert( s[26] == '{' );
    assert( s[66] == '}' );

    // Comma locations
    assert( s[11] == ',' );
    assert( s[18] == ',' );
    assert( s[25] == ',' );
    assert( s[31] == ',' );
    assert( s[36] == ',' );
    assert( s[41] == ',' );
    assert( s[46] == ',' );
    assert( s[51] == ',' );
    assert( s[56] == ',' );
    assert( s[61] == ',' );
}

void ParseValidNFormatString()
{
    using namespace std::literals::string_view_literals;

    std::cout << __func__ << std::endl;

    System::Guid object = System::Guid::Parse( "7e44885fb76d4c05a6f2460a803d8f28"sv );
    System::ReadOnlySpan<std::byte, 16> bytes = object.ToByteArray();

    // Use the hex string values, but without the hyphens...
    assert( bytes[0] == std::byte{0x7e} );
    assert( bytes[1] == std::byte{0x44} );
    assert( bytes[2] == std::byte{0x88} );
    assert( bytes[3] == std::byte{0x5f} );

    assert( bytes[4] == std::byte{0xb7} );
    assert( bytes[5] == std::byte{0x6d} );

    assert( bytes[6] == std::byte{0x4c} );
    assert( bytes[7] == std::byte{0x05} );

    assert( bytes[8] == std::byte{0xa6} );
    assert( bytes[9] == std::byte{0xf2} );

    assert( bytes[10] == std::byte{0x46} );
    assert( bytes[11] == std::byte{0x0a} );
    assert( bytes[12] == std::byte{0x80} );
    assert( bytes[13] == std::byte{0x3d} );
    assert( bytes[14] == std::byte{0x8f} );
    assert( bytes[15] == std::byte{0x28} );
}

void ParseValidDFormatString()
{
    using namespace std::literals::string_view_literals;

    std::cout << __func__ << std::endl;

    System::Guid object = System::Guid::Parse( "7e44885f-b76d-4c05-a6f2-460a803d8f28"sv );
    System::ReadOnlySpan<std::byte, 16> bytes = object.ToByteArray();

    // Use the hex string values, but without the hyphens...
    assert( bytes[0] == std::byte{0x7e} );
    assert( bytes[1] == std::byte{0x44} );
    assert( bytes[2] == std::byte{0x88} );
    assert( bytes[3] == std::byte{0x5f} );

    assert( bytes[4] == std::byte{0xb7} );
    assert( bytes[5] == std::byte{0x6d} );

    assert( bytes[6] == std::byte{0x4c} );
    assert( bytes[7] == std::byte{0x05} );

    assert( bytes[8] == std::byte{0xa6} );
    assert( bytes[9] == std::byte{0xf2} );

    assert( bytes[10] == std::byte{0x46} );
    assert( bytes[11] == std::byte{0x0a} );
    assert( bytes[12] == std::byte{0x80} );
    assert( bytes[13] == std::byte{0x3d} );
    assert( bytes[14] == std::byte{0x8f} );
    assert( bytes[15] == std::byte{0x28} );
}

void ParseValidBFormatString()
{
    using namespace std::literals::string_view_literals;

    std::cout << __func__ << std::endl;

    System::Guid object = System::Guid::Parse( "{7e44885f-b76d-4c05-a6f2-460a803d8f28}"sv );
    System::ReadOnlySpan<std::byte, 16> bytes = object.ToByteArray();

    // Use the hex string values, but without the hyphens...
    assert( bytes[0] == std::byte{0x7e} );
    assert( bytes[1] == std::byte{0x44} );
    assert( bytes[2] == std::byte{0x88} );
    assert( bytes[3] == std::byte{0x5f} );

    assert( bytes[4] == std::byte{0xb7} );
    assert( bytes[5] == std::byte{0x6d} );

    assert( bytes[6] == std::byte{0x4c} );
    assert( bytes[7] == std::byte{0x05} );

    assert( bytes[8] == std::byte{0xa6} );
    assert( bytes[9] == std::byte{0xf2} );

    assert( bytes[10] == std::byte{0x46} );
    assert( bytes[11] == std::byte{0x0a} );
    assert( bytes[12] == std::byte{0x80} );
    assert( bytes[13] == std::byte{0x3d} );
    assert( bytes[14] == std::byte{0x8f} );
    assert( bytes[15] == std::byte{0x28} );
}

void ParseValidPFormatString()
{
    using namespace std::literals::string_view_literals;

    std::cout << __func__ << std::endl;

    System::Guid object = System::Guid::Parse( "(7e44885f-b76d-4c05-a6f2-460a803d8f28)"sv );
    System::ReadOnlySpan<std::byte, 16> bytes = object.ToByteArray();

    // Use the hex string values, but without the hyphens...
    assert( bytes[0] == std::byte{0x7e} );
    assert( bytes[1] == std::byte{0x44} );
    assert( bytes[2] == std::byte{0x88} );
    assert( bytes[3] == std::byte{0x5f} );

    assert( bytes[4] == std::byte{0xb7} );
    assert( bytes[5] == std::byte{0x6d} );

    assert( bytes[6] == std::byte{0x4c} );
    assert( bytes[7] == std::byte{0x05} );

    assert( bytes[8] == std::byte{0xa6} );
    assert( bytes[9] == std::byte{0xf2} );

    assert( bytes[10] == std::byte{0x46} );
    assert( bytes[11] == std::byte{0x0a} );
    assert( bytes[12] == std::byte{0x80} );
    assert( bytes[13] == std::byte{0x3d} );
    assert( bytes[14] == std::byte{0x8f} );
    assert( bytes[15] == std::byte{0x28} );
}

void ParseValidXFormatString()
{
    using namespace std::literals::string_view_literals;

    std::cout << __func__ << std::endl;

    System::Guid object = System::Guid::Parse( "{0x7e44885f,0xb76d,0x4c05,{0xa6,0xf2,0x46,0x0a,0x80,0x3d,0x8f,0x28}}"sv );
    System::ReadOnlySpan<std::byte, 16> bytes = object.ToByteArray();

    // Use the hex string values, but without the hyphens...
    assert( bytes[0] == std::byte{0x7e} );
    assert( bytes[1] == std::byte{0x44} );
    assert( bytes[2] == std::byte{0x88} );
    assert( bytes[3] == std::byte{0x5f} );

    assert( bytes[4] == std::byte{0xb7} );
    assert( bytes[5] == std::byte{0x6d} );

    assert( bytes[6] == std::byte{0x4c} );
    assert( bytes[7] == std::byte{0x05} );

    assert( bytes[8] == std::byte{0xa6} );
    assert( bytes[9] == std::byte{0xf2} );

    assert( bytes[10] == std::byte{0x46} );
    assert( bytes[11] == std::byte{0x0a} );
    assert( bytes[12] == std::byte{0x80} );
    assert( bytes[13] == std::byte{0x3d} );
    assert( bytes[14] == std::byte{0x8f} );
    assert( bytes[15] == std::byte{0x28} );
}

void Run()
{
    std::cout << "Running Guid Tests..." << std::endl;

    ConstructWithSpanOfBytes();
    ConstructWithNFormatString();
    ConstructWithDFormatString();
    ConstructWithBFormatString();
    ConstructWithPFormatString();
    ConstructWithXFormatString();
    EmptyProducesAllZeros();
    AllBitsSetProducesAllBitsSet();
    ToArrayReturnsUnderlyingValues();
    ToStringNoParameter();
    ToStringNParameter();
    ToStringDParameter();
    ToStringBParameter();
    ToStringPParameter();
    ToStringXParameter();
    ParseValidNFormatString();
    ParseValidDFormatString();
    ParseValidBFormatString();
    ParseValidPFormatString();
    ParseValidXFormatString();

    std::cout << "PASSED!" << std::endl;
}

}