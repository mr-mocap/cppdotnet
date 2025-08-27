module;

export module System:DateTimeKind;

export import System:Private_enum;


namespace System
{

export
enum class DateTimeKind
{
    Unspecified, ///@< The time represented is not specified as either local time or Coordinated Universal Time (UTC)
    Utc,         ///@< The time represents UTC
    Local        ///@< The time represented is local time
};

}

namespace System
{

export
template <>
struct EnumPolicy<System::DateTimeKind> : EnumTraitTypes<System::DateTimeKind>
{
    static constexpr std::string_view EnumName = "DateTimeKind";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Unspecified", DateTimeKind::Unspecified },
            { "Utc",         DateTimeKind::Utc         },
            { "Local",       DateTimeKind::Local       }
        };
};

}
