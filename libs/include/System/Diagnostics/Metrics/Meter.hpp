
#include "System/Diagnostics/Metrics/MeterOptions.hpp"
#include "System/Diagnostics/Metrics/Counter.hpp"


namespace System::Diagnostics::Metrics
{

class Meter
{
public:
    Meter() = delete;
    Meter(std::string_view name)
        :
        _name{ name }
    {
    }
    Meter(std::string_view name, std::string_view version)
        :
        _name{ name },
        _version{ version }
    {
    }
    Meter(const MeterOptions &options)
        :
        _name{ options.Name },
        _version{ options.Version }
    {
    }

    std::string_view Name() const { return _name; }
    std::string_view Version() const { return _version; }

    template <class T>
    Counter<T> CreateCounter(std::string_view name, std::string_view unit, std::string_view description)
    {
        return Counter<T>(*this, name, unit, description);
    }
protected:
    std::string _name;
    std::string _version;

    // TODO: Implement Scope, Tags
};

}
