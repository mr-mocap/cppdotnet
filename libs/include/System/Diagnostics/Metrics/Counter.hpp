#include "System/Diagnostics/Metrics/Instrument.hpp"
#include <type_traits>


namespace System::Diagnostics::Metrics
{

namespace Concepts
{

template <class T>
concept IsByte = std::is_same_v<T, std::byte>;

template <class T>
concept IsSignedByte = std::is_same_v<T, std::uint8_t>;

template <class T>
concept IsSignedArithmetic = std::is_arithmetic_v<T> && std::is_signed_v<T>;

template <class T>
concept CounterType = IsByte<T> || IsSignedArithmetic<T> && !IsSignedByte<T>;

}

template <Concepts::CounterType T>
class Counter : public Instrument::SpecificInstrument<T>
{
public:
    Counter() = delete;

    void Add(T delta)
    {
        this->RecordMeasurement( delta );
    }

protected:
    using Instrument::SpecificInstrument<T>::SpecificInstrument;

    friend class Meter;
};

}