#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace System::Diagnostics::Metrics::Concepts
{

template <class T>
concept IsByte = std::is_same_v<T, std::byte>;

template <class T>
concept IsSignedByte = std::is_same_v<T, std::uint8_t>;

template <class T>
concept IsSignedArithmetic = std::is_arithmetic_v<T> && std::is_signed_v<T>;

template <class T>
concept InstrumentType = IsByte<T> || IsSignedArithmetic<T> && !IsSignedByte<T>;

}