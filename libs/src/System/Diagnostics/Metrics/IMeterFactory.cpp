#include "System/Diagnostics/Metrics/IMeterFactory.hpp"
#include <algorithm>


namespace System::Diagnostics::Metrics
{

Meter IMeterFactory::Create(const MeterOptions &options)
{
    auto found = std::ranges::find_if( _cached_meters,
                                       [=](const Meter &current_meter)
                                       {
                                            return (current_meter.Name()    == options.Name) &&
                                                   (current_meter.Version() == options.Version);
                                       }
                                       );

    if ( found != _cached_meters.end() )
        return *found;
    
    // We need to create one since it doesn't exist
    _cached_meters.push_back( Meter( options ) );
    return _cached_meters.back();
}

}