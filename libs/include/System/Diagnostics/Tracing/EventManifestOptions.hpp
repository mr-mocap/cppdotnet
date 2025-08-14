
namespace System::Diagnostics::Tracing
{

enum class EventManifestOptions
{
    None         = 0, //@< No options are specified
    Strict       = 1, //@< Causes an exception to be raised if any inconsistencies occur when writing the manifest file
    AllCultures  = 2, //@< Generates a resources node under the localization folder for every satellite assembly provided
    OnlyIfNeededForRegistration = 4, //@< A manifest is generated only the event source must be registered on the host computer
    AllowEventSourceOverride    = 8  //@< Overrides the default behavior that the current EventSource must be the base class of the user-defined type passed to the write method. This enables the validation of .NET event sources.
};

}

namespace System
{

template <>
struct EnumPolicy<System::Diagnostics::Tracing::EventManifestOptions> : EnumTraitTypes<System::Diagnostics::Tracing::EventManifestOptions>
{
public:

    static constexpr std::string_view EnumName = "EventManifestOptions";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",                        Diagnostics::Tracing::EventManifestOptions::None         },
            { "Strict",                      Diagnostics::Tracing::EventManifestOptions::Strict       },
            { "AllCultures",                 Diagnostics::Tracing::EventManifestOptions::AllCultures  },
            { "OnlyIfNeededForRegistration", Diagnostics::Tracing::EventManifestOptions::OnlyIfNeededForRegistration },
            { "AllowEventSourceOverride",    Diagnostics::Tracing::EventManifestOptions::AllowEventSourceOverride    }
        };
};

}