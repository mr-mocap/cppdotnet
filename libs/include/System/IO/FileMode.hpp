#include "System/Private/enum.hpp"

namespace System::IO
{

enum class FileMode
{
    CreateNew    = 1,
    Create       = 2,
    Open         = 3,
    OpenOrCreate = 4,
    Truncate     = 5,
    Append       = 6
};

}

namespace System
{

template <>
struct EnumPolicy<System::IO::FileMode> : EnumTraitTypes<System::IO::FileMode>
{
    static constexpr std::string_view EnumName = "FileMode";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "CreateNew",    IO::FileMode::CreateNew    },
            { "Create",       IO::FileMode::Create       },
            { "Open",         IO::FileMode::Open         },
            { "OpenOrCreate", IO::FileMode::OpenOrCreate },
            { "Truncate",     IO::FileMode::Truncate     },
            { "Append",       IO::FileMode::Append       }
        };
};

}