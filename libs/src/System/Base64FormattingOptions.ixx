module;

export module System:Base64FormattingOptions;

export import System:Private_enum;


namespace System
{

export
enum class Base64FormattingOptions
{
    None,            ///@< Does not insert line breaks after every 76 characters in the string representation.
    InsertLineBreaks ///@< Inserts line breaks after every 76 characters in the string representation.
};

}

namespace System
{

export
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