module;

export module System:PlatformID;

export import System:Private_enum;

namespace System
{

export
enum class PlatformID
{
    Win32S       = 0,
    Win32Windows = 1,
    Win32NT = 2,
    WinCE   = 3,
    Unix    = 4,
    Xbox    = 5,
    MacOSX  = 6
};

}

namespace System
{

export
template <>
struct EnumPolicy<System::PlatformID> : EnumTraitTypes<System::PlatformID>
{
    static constexpr std::string_view EnumName = "PlatformID";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Win32S",       PlatformID::Win32S       },
            { "Win32Windows", PlatformID::Win32Windows },
            { "Win32NT",      PlatformID::Win32NT      },
            { "WinCE",        PlatformID::WinCE        },
            { "Unix",         PlatformID::Unix         },
            { "Xbox",         PlatformID::Xbox         },
            { "MacOSX",       PlatformID::MacOSX       }
        };
};

}
