#include "System/Diagnostics/ActivitySource.hpp"
#include "System/Private/private.hpp"


namespace System::Diagnostics
{

Activity ActivitySource::CreateActivity(std::string_view  name,
                                        ActivityKind      kind,
                                        ActivityContext  &parent_context,
                                        ActivityIdFormat  id_format)
{
    UNUSED(kind);
    UNUSED(parent_context);
    UNUSED(id_format);

    return Activity(name);
}

void ActivitySource::AddActivityListener(const ActivityListener &listener)
{
    UNUSED(listener);
}

bool ActivitySource::HasListeners() const
{
    return false;
}

}