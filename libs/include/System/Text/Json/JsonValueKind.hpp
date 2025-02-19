#pragma once


namespace System::Text::Json
{

enum class JsonValueKind
{
    Undefined = 0,  // There is no value (as distinct from Null)
    Object    = 1,  // A JSON Object
    Array     = 2,  // A JSON array
    String    = 3,  // A JSON string
    Number    = 4,  // A JSON number
    True      = 5,  // The JSON true value
    False     = 6,  // The JSON false value
    Null      = 7,  // The JSON value null
};

}