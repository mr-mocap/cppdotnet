#include "System/Private/enum.hpp"


namespace System::IO
{

enum class UnixFileMode
{
    None          = 0,    ///@< No Permissions
    OtherExecute  = 1,    ///@< Execute permission for others
    OtherWrite    = 2,    ///@< Write permission for others
    OtherRead     = 4,    ///@< Read permission for others
    GroupExecute  = 8,    ///@< Execute permission for group
    GroupWrite    = 16,   ///@< Write permission for group
    GroupRead     = 32,   ///@< Read permission for group
    UserExecute   = 64,   ///@< Execute permission for user
    UserWrite     = 128,  ///@< Write permission for user
    UserRead      = 256,  ///@< Read permission for user
    StickyBit     = 512,  ///@< Sticky bit permission
    SetGroup      = 1024, ///@< Set group permission
    SetUser       = 2048  ///@< Set user permission
};

}

namespace System
{

template <>
struct EnumPolicy<System::IO::UnixFileMode> : EnumTraitTypes<System::IO::UnixFileMode>
{
    static constexpr std::string_view EnumName = "UnixFileMode";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",         IO::UnixFileMode::None         },
            { "OtherExecute", IO::UnixFileMode::OtherExecute },
            { "OtherWrite",   IO::UnixFileMode::OtherWrite   },
            { "OtherRead",    IO::UnixFileMode::OtherRead    },
            { "GroupExecute", IO::UnixFileMode::GroupExecute },
            { "GroupWrite",   IO::UnixFileMode::GroupWrite   },
            { "GroupRead",    IO::UnixFileMode::GroupRead    },
            { "UserExecute",  IO::UnixFileMode::UserExecute  },
            { "UserWrite",    IO::UnixFileMode::UserWrite    },
            { "UserRead",     IO::UnixFileMode::UserRead     },
            { "StickyBit",    IO::UnixFileMode::StickyBit    },
            { "SetGroup",     IO::UnixFileMode::SetGroup     },
            { "SetUser",      IO::UnixFileMode::SetUser      }
        };
};

}