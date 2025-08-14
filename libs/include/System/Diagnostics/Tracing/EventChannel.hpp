
namespace System::Diagnostics::Tracing
{

enum class EventChannel
{
    None        =  0,  //@< No channel specified
    Admin       = 16,  //@< The administrator log channel
    Operational = 17,  //@< The operational log channel
    Analytic    = 18,  //@< The analytic log channel
    Debug       = 19   //@< The debug channel
};

}

namespace System
{

template <>
struct EnumPolicy<System::Diagnostics::Tracing::EventChannel> : EnumTraitTypes<System::Diagnostics::Tracing::EventChannel>
{
public:

    static constexpr std::string_view EnumName = "EventChannel";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",        Diagnostics::Tracing::EventChannel::None        },
            { "Admin",       Diagnostics::Tracing::EventChannel::Admin       },
            { "Operational", Diagnostics::Tracing::EventChannel::Operational },
            { "Analytin",    Diagnostics::Tracing::EventChannel::Analytic    },
            { "Debug",       Diagnostics::Tracing::EventChannel::Debug       }
        };
};

}