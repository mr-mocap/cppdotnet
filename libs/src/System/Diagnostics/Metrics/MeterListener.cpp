#include "System/Diagnostics/Metrics/MeterListener.hpp"


namespace System::Diagnostics::Metrics
{

void MeterListener::Start()
{
}

void MeterListener::DisableMeasurement(Instrument &)
{
}

void MeterListener::EnableMeasurementEvents(Instrument &)
{
}

void MeterListener::RecordObservableInstruments()
{
}

std::string MeterListener::ToString() const
{
    return "UNIMPLEMENTED";
}

}