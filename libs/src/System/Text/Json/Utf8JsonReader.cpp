#include "System/Text/Json/Utf8JsonReader.hpp"


namespace System::Text::Json
{

JsonTokenType Utf8JsonReader::TokenType() const
{
    return JsonTokenType::None;
}

bool Utf8JsonReader::Read()
{
    return false;
}

}