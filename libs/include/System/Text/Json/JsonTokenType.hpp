#pragma once

namespace System::Text::Json
{

enum class JsonTokenType
{
    None         = 0,  // There is no value (as distinct from Null).  This is the default token type if no data has been read by the Utf8JsonReader.
    StartObject  = 1,  // The token type is the start of a JSON object
    EndObject    = 2,  // The token type is the end of a JSON object
    StartArray   = 3,  // The token type is the start of a JSON array
    EndArray     = 4,  // The token type is the end of a JSON array
    PropertyName = 5,  // The token type is a JSON property name
    Comment      = 6,  // The token type is a comment string
    String       = 7,  // The token type is a JSON string
    Number       = 8,  // The token type is JSON number
    True         = 9,  // The token type is the JSON literal true
    False        = 10, // The token type is the JSON literal false
    Null         = 11  // The token type is the JSON literal null
};

}