#include "System/Private/Delegate.hpp"
#include "System/Diagnostics/Metrics/Instrument.hpp"


namespace System::Diagnostics::Metrics
{

template <class T>
class MeasurementCallback : Delegate<Instrument &, const T &>
{
    using Delegate<Instrument &, const T &>::Delegate;
};

}