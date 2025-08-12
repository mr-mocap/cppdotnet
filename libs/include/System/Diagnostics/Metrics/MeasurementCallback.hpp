#pragma once

import "System/Private/Delegate.hpp";
import "System/Diagnostics/Metrics/Instrument.hpp";


namespace System::Diagnostics::Metrics
{

template <class T>
class MeasurementCallback : Delegate<Instrument &, const T &>
{
    using Delegate<Instrument &, const T &>::Delegate;
};

}