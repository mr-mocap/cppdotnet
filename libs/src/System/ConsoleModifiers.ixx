module;

export module System:ConsoleModifiers;

export import System:Private_enum;


namespace System
{

export
enum class ConsoleModifiers
{
    None    = 0,
    Alt     = 1, ///@< The left or right ALT modifier key
    Shift   = 2, ///@< The left or right SHIFT modifier key
    Control = 4  ///@< The left or right CTRL modifier key
};

}

namespace System
{

export
template <>
struct EnumPolicy<ConsoleModifiers> : EnumTraitTypes<ConsoleModifiers>
{
    static constexpr std::string_view EnumName = "ConsoleModifiers";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",    ConsoleModifiers::None    },
            { "Alt",     ConsoleModifiers::Alt     },
            { "Shift",   ConsoleModifiers::Shift   },
            { "Control", ConsoleModifiers::Control }
        };
};

}