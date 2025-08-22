#include "System/Private/enum.hpp"

namespace System::IO
{

enum class FileAccess
{
    Read      = 1,
    Write     = 2,
    ReadWrite = 3
};

}

namespace System
{

template <>
struct EnumPolicy<System::IO::FileAccess> : EnumTraitTypes<System::IO::FileAccess>
{
    static constexpr std::string_view EnumName = "FileAccess";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Read",      IO::FileAccess::Read      },
            { "Write",     IO::FileAccess::Write     },
            { "ReadWrite", IO::FileAccess::ReadWrite }
        };
};

}