#include "System/Private/enum.hpp"

namespace System::IO
{

enum class SeekOrigin
{
    Begin,   ///@< Specifies the beginning of a stream
    Current, ///@< Specifies the current position within a stream
    End      ///@< Specifies the end of a stream
};

}

namespace System
{

template <>
struct EnumPolicy<System::IO::SeekOrigin> : EnumTraitTypes<System::IO::SeekOrigin>
{
    static constexpr std::string_view EnumName = "SeekOrigin";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Begin",   IO::SeekOrigin::Begin   },
            { "Current", IO::SeekOrigin::Current },
            { "End",     IO::SeekOrigin::End     }
        };
};

}