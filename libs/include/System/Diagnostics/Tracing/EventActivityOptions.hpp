
namespace System::Diagnostics::Tracing
{

enum class EventActivityOptions
{
    None       = 0, //@< Use the default behavior for start and stop tracking.
    Disable    = 2, //@< Turn off start and stop tracking.
    Recursive  = 4, //@< Allow recursive activity starts. By default, an activity cannot be recursive. That is, a sequence of Start A, Start A, Stop A, Stop A is not allowed. Unintentional recursive activities can occur if the app executes and for some the stop is not reached before another start is called.
    Detachable = 8  //@< Allow overlapping activities. By default, activity starts and stops must be property nested. That is, a sequence of Start A, Start B, Stop A, Stop B is not allowed will result in B stopping at the same time as A.
};

}

namespace System
{

template <>
struct EnumPolicy<System::Diagnostics::Tracing::EventActivityOptions> : EnumTraitTypes<System::Diagnostics::Tracing::EventActivityOptions>
{
public:

    static constexpr std::string_view EnumName = "EventActivityOptions";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",       Diagnostics::Tracing::EventActivityOptions::None       },
            { "Disable",    Diagnostics::Tracing::EventActivityOptions::Disable    },
            { "Recursive",  Diagnostics::Tracing::EventActivityOptions::Recursive  },
            { "Detachable", Diagnostics::Tracing::EventActivityOptions::Detachable }
        };
};

}