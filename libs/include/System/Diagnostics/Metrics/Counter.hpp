#pragma once

#include "System/Diagnostics/Metrics/Instrument.hpp"
#include <type_traits>


namespace System::Diagnostics::Metrics
{

namespace Concepts
{

template <class T>
concept CounterType = std::is_same_v<T, std::byte> || (std::is_arithmetic_v<T> && std::is_signed_v<T> && !std::is_same_as_v<T, std::uint8_t>);

}

template <Concepts::CounterType T>
class Counter : public Instrument<T>
{
public:

    void Add(const T &delta);

protected:
};

}