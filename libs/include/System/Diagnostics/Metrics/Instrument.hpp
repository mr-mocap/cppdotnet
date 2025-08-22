#include "System/Private/private.hpp"
#include <string>
#include <string_view>
#include <memory>
#include <any>

namespace System::Diagnostics::Metrics
{

class Meter;

class Instrument
{
public:

    template <class T>
    class SpecificInstrument
    {
    public:
        SpecificInstrument() = delete;

        bool Enabled() const { return false; } // TODO: FIXME

        virtual bool IsObservable() const { return false; }

        const class Meter &Meter() const { return _meter; }
              class Meter &Meter()       { return _meter; }

        std::string_view Name() const { return _name; }

        std::string_view Description() const { return _description; }

        std::string_view Unit() const { return _unit; }

        // TODO: Implement Tags

        virtual std::string ToString() const
        {
            return "UNIMPLEMENTED";
        }
    protected:
        class Meter &_meter;
        std::string  _name;
        std::string  _description;
        std::string  _unit;

        SpecificInstrument(class Meter &meter, std::string_view name)
            :
            _meter( meter ),
            _name( name )
        {
        }

        SpecificInstrument(class Meter &meter,
                std::string_view name,
                std::string_view unit,
                std::string_view description)
            :
            _meter( meter ),
            _name( name ),
            _description( description ),
            _unit( unit )
        {
        }

        void Publish()
        {
        }

        void RecordMeasurement(T measurement)
        {
            UNUSED(measurement);
        }

        friend class Instrument;
    };

protected:

    struct InternalInterface
    {
        virtual ~InternalInterface() { }

        virtual bool Enabled() const = 0;
        virtual bool IsObservable() const = 0;
        virtual const class Meter &Meter() const = 0;
        virtual       class Meter &Meter()       = 0;
        virtual std::string_view Name() const = 0;
        virtual std::string_view Description() const = 0;
        virtual std::string_view Unit() const = 0;
        virtual       std::string      ToString() const = 0;

        virtual void Publish() = 0;
        virtual void RecordMeasurement(std::any measurement) = 0;

        virtual std::unique_ptr<InternalInterface> Clone() = 0;
        virtual std::unique_ptr<InternalInterface> Empty() = 0;
    };

    template <class SpecificInstrumentType>
    struct GeneralizedInterface : InternalInterface
    {
        GeneralizedInterface() = default;
        GeneralizedInterface(SpecificInstrument<SpecificInstrumentType> &input) : specific_instrument( input ) { }
        GeneralizedInterface(SpecificInstrument<SpecificInstrumentType> &&input) : specific_instrument( std::move(input) ) { }
        ~GeneralizedInterface() override { }
          
        // Default copy and move
        GeneralizedInterface(const GeneralizedInterface &other) = default;
        GeneralizedInterface(GeneralizedInterface &&other) = default;

        GeneralizedInterface &operator =(const GeneralizedInterface &) = default;
        GeneralizedInterface &operator =(GeneralizedInterface &&) = default;

        bool Enabled() const override { return specific_instrument.Enabled(); }
        bool IsObservable() const override { return specific_instrument.IsObservable(); }
        const class Meter &Meter() const override { return specific_instrument.Meter(); }
              class Meter &Meter()       override { return specific_instrument.Meter(); }
        std::string_view Name() const override { return specific_instrument.Name(); }
        std::string_view Description() const override { return specific_instrument.Description(); }
        std::string_view Unit() const override { return specific_instrument.Unit(); }
        std::string      ToString() const override { return specific_instrument.ToString(); }

        void Publish() override { specific_instrument.Publish(); }
        void RecordMeasurement(std::any measurement) override
        {
            specific_instrument.RecordMeasurement( std::any_cast<SpecificInstrumentType>(measurement) );
        }

        std::unique_ptr<InternalInterface> Clone() override
        {
            return std::make_unique<GeneralizedInterface>(specific_instrument);
        }

        std::unique_ptr<InternalInterface> Empty() override
        {
            return std::make_unique_for_overwrite<GeneralizedInterface>();
        }

        SpecificInstrument<SpecificInstrumentType> specific_instrument;
    };

public:
    Instrument() = delete;

    template <class SpecificInstrumentType>
    Instrument(SpecificInstrument<SpecificInstrumentType> &input)
      :
      _data( std::make_unique<GeneralizedInterface<SpecificInstrumentType>>(input) )
    {
    }

    template <class SpecificInstrumentType>
    Instrument(SpecificInstrument<SpecificInstrumentType> &&input)
      :
      _data( std::make_unique<GeneralizedInterface<SpecificInstrumentType>>( std::move(input) ) )
    {
    }

    Instrument(const Instrument &other)
      :
      _data( other._data->Clone() )
    {
    }
    Instrument(Instrument &other)
      :
      _data( other._data->Clone() )
    {
    }
    Instrument(Instrument &&other)
      :
      _data( other._data->Empty() )
    {
        std::swap( _data, other._data );
    }

    Instrument &operator =(const Instrument &other)
    {
        _data = other._data->Clone();
        return *this;
    }

    Instrument &operator =(Instrument &&other) = delete;

    bool Enabled() const { return _data->Enabled(); }
    bool IsObservable() const { return _data->IsObservable(); }
    const class Meter &Meter() const { return _data->Meter(); }
          class Meter &Meter()       { return _data->Meter(); }
    std::string_view Name() const { return _data->Name(); }
    std::string_view Description() const { return _data->Description(); }
    std::string_view Unit() const { return _data->Unit(); }
          std::string      ToString() const { return _data->ToString(); }
protected:
    std::unique_ptr<InternalInterface> _data;

    void Publish()
    {
        _data->Publish();
    }

    void RecordMeasurement(std::any measurement)
    {
        _data->RecordMeasurement( measurement );
    }
};

}
