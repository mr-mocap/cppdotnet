#include "System/Diagnostics/ActivitySource.hpp"


namespace System::Diagnostics
{

Activity ActivitySource::CreateActivity(std::string_view  name,
                                        ActivityKind      kind,
                                        ActivityContext  &parent_context,
                                        ActivityIdFormat  id_format)
{
    return Activity(name);
}

}