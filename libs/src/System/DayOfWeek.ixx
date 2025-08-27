module;

export module System:DayOfWeek;

export import System:Private_enum;


namespace System
{

export
enum class DayOfWeek
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

}

namespace System
{

export
template <>
struct EnumPolicy<System::DayOfWeek> : EnumTraitTypes<System::DayOfWeek>
{
    static constexpr std::string_view EnumName = "DayOfWeek";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Sunday",    DayOfWeek::Sunday    },
            { "Monday",    DayOfWeek::Monday    },
            { "Tuesday",   DayOfWeek::Tuesday   },
            { "Wednesday", DayOfWeek::Wednesday },
            { "Thursday",  DayOfWeek::Thursday  },
            { "Friday",    DayOfWeek::Friday    },
            { "Saturday",  DayOfWeek::Saturday  }
        };
};

}
