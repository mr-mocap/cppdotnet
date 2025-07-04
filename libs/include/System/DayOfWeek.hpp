#pragma once

#include "System/Private/enum.hpp"


namespace System
{

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

template <>
struct EnumPolicy<System::DayOfWeek>
{
public:
    using value_type = System::DayOfWeek;
    using name_value_pair_type = std::pair<const char *, value_type>;

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
