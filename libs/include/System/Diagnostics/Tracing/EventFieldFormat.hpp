#pragma once


namespace System::Diagnostics::Tracing
{

enum class EventFieldFormat
{
    Default     = 0,
    String	    = 2,
    Boolean     = 3,
    Hexadecimal = 4,
    Xml         = 11,
    Json        = 12,
    HResult     = 15	
};

}

namespace System
{

template <>
struct EnumPolicy<System::Diagnostics::Tracing::EventFieldFormat>
{
public:
    using value_type = System::Diagnostics::Tracing::EventFieldFormat;
    using name_value_pair_type = std::pair<const char *, value_type>;

    static constexpr std::string_view EnumName = "EventFieldFormat";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Default",     Diagnostics::Tracing::EventFieldFormat::Default     },
            { "String",      Diagnostics::Tracing::EventFieldFormat::String      },
            { "Boolean",     Diagnostics::Tracing::EventFieldFormat::Boolean     },
            { "Hexadecimal", Diagnostics::Tracing::EventFieldFormat::Hexadecimal },
            { "Xml",         Diagnostics::Tracing::EventFieldFormat::Xml         },
            { "Json",        Diagnostics::Tracing::EventFieldFormat::Json        },
            { "HResult",     Diagnostics::Tracing::EventFieldFormat::HResult     }
        };
};

}