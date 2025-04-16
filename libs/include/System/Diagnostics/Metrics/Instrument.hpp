#pragma once

#include "System/Diagnostics/Metrics/Meter.hpp"


namespace System::Diagnostics::Metrics
{

class Instrument
{
public:

    bool Enabled() const { return false; } // TODO: FIXME

    virtual bool IsObservable() const { return false; }

    const Meter &Meter() const { return _meter; }
          Meter &Meter()       { return _meter; }

    const std::string_view Name() const { return _meter.Name(); }

    const std::string_view Description() const { return _description; }

    const std::string_view Unit() const { return _meter.Unit(); }

    // TODO: Implement Tags

    virtual std::string ToString() const;
protected:
    Meter       _meter;
    std::string _name;
    std::string _description;
    std::string _unit;

    Instrument(Meter &meter, const std::string_view name)
        :
        _meter( meter ),
        _name{ name }
    {
    }

    Instrument(Meter &meter,
               const std::string_view name,
               const std::string_view unit,
               const std::string_view description)
        :
        _meter( meter ),
        _name( name ),
        _description( description ),
        _unit( unit )
    {
    }

    void Publish();
};


template <class T>
class Instrument : public Instrument
{
public:

protected:
    Instrument(Meter &meter, const std::string_view name)
        :
        Instrument( meter, name )
    {
    }

    Instrument(Meter &meter,
               const std::string_view name,
               const std::string_view unit,
               const std::string_view description)
        :
        Instrument( meter, name, unit, description )
    {
    }

    void RecordMeasurement(const T &measurement)
    {
    }
};

}
