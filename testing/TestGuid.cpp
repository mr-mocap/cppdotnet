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

void Run()
{
    std::cout << "Running Guid Tests..." << std::endl;

    ConstructWithSpanOfBytes();
    EmptyProducesAllZeros();
    AllBitsSetProducesAllBitsSet();
    ToArrayReturnsUnderlyingValues();

    std::cout << "PASSED!" << std::endl;
}

}