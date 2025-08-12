#pragma once

import "System/Private/enum.hpp";


namespace System
{

enum class Base64FormattingOptions
{
    None,            ///@< Does not insert line breaks after every 76 characters in the string representation.
    InsertLineBreaks ///@< Inserts line breaks after every 76 characters in the string representation.
};

}

namespace System
{

template <>
struct EnumPolicy<System::Base64FormattingOptions> : EnumTraitTypes<System::Base64FormattingOptions>
{
    static constexpr std::string_view EnumName = "Base64FormattingOptions";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",             Base64FormattingOptions::None             },
            { "InsertLineBreaks", Base64FormattingOptions::InsertLineBreaks }
        };
};

}