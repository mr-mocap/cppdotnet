#pragma once

#include "System/Diagnostics/Metrics/Instrument.hpp"

namespace System::Diagnostics::Metrics
{

template <Concepts::InstrumentType T>
class Counter : public Instrument::SpecificInstrument<T>
{
public:
    Counter() = delete;
   ~Counter() = default;

    void Add(T delta)
    {
        this->RecordMeasurement( delta );
    }

protected:
    using Instrument::SpecificInstrument<T>::SpecificInstrument;

    friend class Meter;
};

}