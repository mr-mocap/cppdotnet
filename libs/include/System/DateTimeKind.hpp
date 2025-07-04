#pragma once

#include "System/Private/enum.hpp"


namespace System
{

enum class DateTimeKind
{
    Unspecified, ///@< The time represented is not specified as either local time or Coordinated Universal Time (UTC)
    Utc,         ///@< The time represents UTC
    Local        ///@< The time represented is local time
};

}

namespace System
{

template <>
struct EnumPolicy<System::DateTimeKind>
{
public:
    using value_type = System::DateTimeKind;
    using name_value_pair_type = std::pair<const char *, value_type>;

    static constexpr std::string_view EnumName = "DateTimeKind";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Unspecified", DateTimeKind::Unspecified },
            { "Utc",         DateTimeKind::Utc         },
            { "Local",       DateTimeKind::Local       }
        };
};

}
