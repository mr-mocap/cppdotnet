#include "System/Diagnostics/ActivitySource.hpp"
#include "System/Diagnostics/ActivityListener.hpp"
#include "System/Collections/Generic/List.hpp"
#include "System/Private/private.hpp"


namespace System::Diagnostics
{

static Collections::Generic::List<ActivityListener> ActivityListeners;
static Collections::Generic::List<std::string>      GlobalActivitySourcesByName;

ActivitySource::ActivitySource(std::string_view name)
    :
    _name( name )
{
    GlobalActivitySourcesByName.Add( _name );
}

ActivitySource::ActivitySource(std::string_view name, std::string_view version)
    :
    _name( name ),
    _version( version )
{
    GlobalActivitySourcesByName.Add( _name );
}

ActivitySource::~ActivitySource()
{
    Dispose();
}

std::optional<Activity> ActivitySource::CreateActivity(std::string_view  name,
                                                       ActivityKind      kind,
                                                       ActivityContext  &parent_context,
                                                       ActivityIdFormat  id_format)
{
    UNUSED(kind);
    UNUSED(parent_context);
    UNUSED(id_format);

    if ( HasListeners() )
    {
        Activity activity(name);

        return activity;
    }

    return {};
}

void ActivitySource::AddActivityListener(const ActivityListener &listener)
{
    ActivityListeners.Add( listener );
}

bool ActivitySource::HasListeners() const
{
    return ActivityListeners.Exists(
        [this](const ActivityListener &listener) -> bool
        {
            if ( listener.ShouldListenTo() )
                return listener.ShouldListenTo()( *this );
            return false;
        }
    );
}

void ActivitySource::Dispose()
{
    GlobalActivitySourcesByName.Remove( _name );
}

}