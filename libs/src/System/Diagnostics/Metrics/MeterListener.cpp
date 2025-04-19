#include "System/Diagnostics/Metrics/MeterListener.hpp"


namespace System::Diagnostics::Metrics
{

void MeterListener::Start()
{
}

void MeterListener::DisableMeasurement(Instrument &instrument)
{
}

void MeterListener::EnableMeasurementEvents(Instrument &instrument)
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