module;

export module System:TypeCode;

export import System:Private_enum;

namespace System
{

export
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

export
template <>
struct EnumPolicy<System::TypeCode> : EnumTraitTypes<System::TypeCode>
{
    static constexpr std::string_view EnumName = "TypeCode";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Empty",    TypeCode::Empty    },
            { "Object",   TypeCode::Object   },
            { "DBNull",   TypeCode::DBNull   },
            { "Boolean",  TypeCode::Boolean  },
            { "Char",     TypeCode::Char     },
            { "SByte",    TypeCode::SByte    },
            { "Byte",     TypeCode::Byte     },
            { "Int16",    TypeCode::Int16    },
            { "UInt16",   TypeCode::UInt16   },
            { "Int32",    TypeCode::Int32    },
            { "UInt32",   TypeCode::UInt32   },
            { "Int64",    TypeCode::Int64    },
            { "UInt64",   TypeCode::UInt64   },
            { "Single",   TypeCode::Single   },
            { "Double",   TypeCode::Double   },
            { "Decimal",  TypeCode::Decimal  },
            { "DateTime", TypeCode::DateTime },
            { "String",   TypeCode::String   }
        };
};

}
