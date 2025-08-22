#include "System/Private/enum.hpp"

namespace System::Diagnostics::Tracing
{

enum class EventSourceSettings
{
    Default                      = 0, //@< None of the special configuration options are enabled
    ThrowOnEventWriteErrors      = 1, //@< The event source throws an exception when an error occurs
    EtwManifestEventFormat       = 4, //@< The ETW listener should use a manifest-based format when raising events. Setting this option is a directive to the ETW listener should use manifest-based format when raising events. This is the default option when defining a type derived from EventSource using one of the protected EventSource constructors.
    EtwSelfDescribingEventFormat = 8, //@< The ETW listener should use self-describing event format. This is the default option when creating a new instance of the EventSource using one of the public EventSource constructors.
};

}

namespace System
{

template <>
struct EnumPolicy<System::Diagnostics::Tracing::EventSourceSettings> : EnumTraitTypes<System::Diagnostics::Tracing::EventSourceSettings>
{
public:

    static constexpr std::string_view EnumName = "EventSourceSettings";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Default",                      Diagnostics::Tracing::EventSourceSettings::Default                      },
            { "ThrowOnEventWriteErrors",      Diagnostics::Tracing::EventSourceSettings::ThrowOnEventWriteErrors      },
            { "EtwManifestEventFormat",       Diagnostics::Tracing::EventSourceSettings::EtwManifestEventFormat       },
            { "EtwSelfDescribingEventFormat", Diagnostics::Tracing::EventSourceSettings::EtwSelfDescribingEventFormat }
        };
};

}