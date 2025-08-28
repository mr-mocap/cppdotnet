module;

export module System:Base;

export import System:Private_enum;

namespace System
{

export
enum class Base
{
    Binary = 2,
    Octal  = 8,
    Decimal = 10,
    Hexadecimal = 16
};

}

namespace System
{

export
template <>
struct EnumPolicy<System::Base> : EnumTraitTypes<System::Base>
{
    static constexpr std::string_view EnumName = "Base";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Binary",      System::Base::Binary      },
            { "Octal",       System::Base::Octal       },
            { "Decimal",     System::Base::Decimal     },
            { "Hexadecimal", System::Base::Hexadecimal }
        };
};

}
