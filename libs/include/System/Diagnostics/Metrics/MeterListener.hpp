#include "System/Action.hpp"
#include "System/Diagnostics/Metrics/Instrument.hpp"
#include "System/Diagnostics/Metrics/MeasurementCallback.hpp"
#include <string>


namespace System::Diagnostics::Metrics
{

class MeterListener
{
public:
    MeterListener();

    Action<Instrument &, MeterListener &> &InstrumentPublished() { return _instrument_published_delegate; }
    Action<Instrument &>                  &MeasurementsCompleted() { return _measurements_completed_delegate; }
    //Action<Instrument &, Object &> MeasurementsCompleted() { return _measurements_completed_delegate; }

    void Start();

    void DisableMeasurement(Instrument &instrument);
    void EnableMeasurementEvents(Instrument &instrument);

    void RecordObservableInstruments();

    template <class T>
    void SetMeasurementEventCallback(MeasurementCallback<T> measurementCallback)
    {
    }

    std::string ToString() const;
protected:
    Action<Instrument &, MeterListener &> _instrument_published_delegate;
    Action<Instrument &>                  _measurements_completed_delegate;
    //Action<Instrument &, Object &> _measurements_completed_delegate;
};

}