module;

export module System:ConsoleColor;

export import System:Private_enum;


namespace System
{

export
enum class ConsoleColor
{
    Black,
    DarkBlue,
    DarkGreen,
    DarkCyan,
    DarkRed,
    DarkMagenta,
    DarkYellow,
    Gray,
    DarkGray,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Yellow,
    White
};

}

namespace System
{

export
template <>
struct EnumPolicy<System::ConsoleColor> : EnumTraitTypes<System::ConsoleColor>
{
    static constexpr std::string_view EnumName = "ConsoleColor";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Black",       ConsoleColor::Black       },
            { "DarkBlue",    ConsoleColor::DarkBlue    },
            { "DarkGreen",   ConsoleColor::DarkGreen   },
            { "DarkCyan",    ConsoleColor::DarkCyan    },
            { "DarkRed",     ConsoleColor::DarkRed     },
            { "DarkMagenta", ConsoleColor::DarkMagenta },
            { "DarkYellow",  ConsoleColor::DarkYellow  },
            { "Gray",        ConsoleColor::Gray        },
            { "DarkGray",    ConsoleColor::DarkGray    },
            { "Blue",        ConsoleColor::Blue        },
            { "Green",       ConsoleColor::Green       },
            { "Cyan",        ConsoleColor::Cyan        },
            { "Red",         ConsoleColor::Red         },
            { "Magenta",     ConsoleColor::Magenta     },
            { "Yellow",      ConsoleColor::Yellow      },
            { "White",       ConsoleColor::White       }
        };
};

}