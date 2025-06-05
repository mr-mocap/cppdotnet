#pragma once

#include "System/Private/enum.hpp"

namespace System
{

enum class TypeCode
{
    Empty    = 0,
    Object   = 1,
    DBNull   = 2,
    Boolean  = 3,
    Char     = 4,
    SByte    = 5,
    Byte     = 6,
    Int16    = 7,
    UInt16   = 8,
    Int32    = 9,
    UInt32   = 10,
    Int64    = 11,
    UInt64   = 12,
    Single   = 13,
    Double   = 14,
    Decimal  = 15,
    DateTime = 16,

    String = 18
};

}

namespace System
{

template <>
struct EnumTraits<System::TypeCode> : EnumTraitTypes<System::TypeCode>
{
    static auto EnumName() -> std::string_view { return "TypeCode"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Empty",    System::TypeCode::Empty    },
            { "Object",   System::TypeCode::Object   },
            { "DBNull",   System::TypeCode::DBNull   },
            { "Boolean",  System::TypeCode::Boolean  },
            { "Char",     System::TypeCode::Char     },
            { "SByte",    System::TypeCode::SByte    },
            { "Byte",     System::TypeCode::Byte     },
            { "Int16",    System::TypeCode::Int16    },
            { "UInt16",   System::TypeCode::UInt16   },
            { "Int32",    System::TypeCode::Int32    },
            { "UInt32",   System::TypeCode::UInt32   },
            { "Int64",    System::TypeCode::Int64    },
            { "UInt64",   System::TypeCode::UInt64   },
            { "Single",   System::TypeCode::Single   },
            { "Double",   System::TypeCode::Double   },
            { "Decimal",  System::TypeCode::Decimal  },
            { "DateTime", System::TypeCode::DateTime },
            { "String",   System::TypeCode::String   }
        };

    static constexpr auto NameValuePairs() -> std::span<const name_value_pair_type>
    {
        return std::span{ NameValueArray };
    }

    static constexpr auto Count() -> std::size_t { return NameValuePairs().size(); }

    static constexpr auto Names() -> std::ranges::keys_view<std::span<const name_value_pair_type>>
    {
        return std::views::keys( NameValuePairs() );
    }

    static constexpr auto Values() -> std::ranges::values_view<std::span<const name_value_pair_type>>
    {
        return std::views::values( NameValuePairs() );
    }

    static constexpr auto ValuesAsUnderlyingType()
    {
        auto to_underlying_type = [](const value_type item) { return static_cast<underlying_type>(item); };

        return Values() | std::views::transform( to_underlying_type );
    }

    static constexpr bool IsDefined(value_type value)
    {
        return std::ranges::find( NameValuePairs(),
                                  value,
                                  &name_value_pair_type::second
                                ) != NameValuePairs().end();
    }

    static constexpr bool IsDefined(underlying_type value)
    {
        return IsDefined( static_cast<value_type>(value) );
    }

    static constexpr bool IsDefined(std::string_view value_string)
    {
        return std::ranges::find( NameValuePairs(),
                                  value_string,
                                  &name_value_pair_type::first
                                ) != NameValuePairs().end();
    }

    static constexpr auto ToName(value_type value) -> std::string_view
    {
        auto found = std::ranges::find( NameValuePairs(),
                                        value,
                                        &name_value_pair_type::second
                                      );

        if ( found == NameValuePairs().end() )
            return {};

        return found->first;
    }

    static constexpr auto ToName(underlying_type value) -> std::string_view
    {
        return ToName( static_cast<value_type>(value) );
    }

    static constexpr value_type min() { return System::TypeCode::Empty; }
    static constexpr value_type max() { return System::TypeCode::String; }
};

}
