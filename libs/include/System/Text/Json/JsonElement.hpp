#pragma once

#include "System/Text/Json/JsonValueKind.hpp"
#include "System/Exception.hpp"

#include <variant>


namespace System::Text::Json
{

class JsonElement
{
public:
    JsonElement() = default;

    const JsonElement Item() const
    {
        using namespace std::literals;

        if ( _kind != JsonValueKind::Array )
            ThrowWithTarget( System::InvalidOperationException{ "JsonElement is not an 'Array' type"sv } );

        // IndexOutOfRangeException

        // ObjectDisposedException

        return *this;
    }
    JsonElement Item()
    {
        using namespace std::literals;

        if ( _kind != JsonValueKind::Array )
            ThrowWithTarget( System::InvalidOperationException{ "JsonElement is not an 'Array' type"sv } );

        // IndexOutOfRangeException

        // ObjectDisposedException

        return *this;
    }

    JsonValueKind ValueKind() const { return _kind; }

    size_t GetArrayLength() const
    {
        using namespace std::literals;

        if ( _kind != JsonValueKind::Array )
            ThrowWithTarget( System::InvalidOperationException{ "JsonElement is not an 'Array' type"sv } );

        // ObjectDisposedException

        return 0;
    }
protected:
    JsonValueKind _kind = JsonValueKind::Undefined;
#if 0
    std::variant<int, int, std::vector<>, std::string, int, bool, bool, int> _item;

    Undefined = 0,  // There is no value (as distinct from Null)
    Object    = 1,  // A JSON Object
    Array     = 2,  // A JSON array
    String    = 3,  // A JSON string
    Number    = 4,  // A JSON number
    True      = 5,  // The JSON true value
    False     = 6,  // The JSON false value
    Null      = 7,  // The JSON value null
#endif
};

}