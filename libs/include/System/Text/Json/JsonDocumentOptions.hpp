#include "System/Text/Json/JsonCommentHandling.hpp"

namespace System::Text::Json
{

class JsonDocumentOptions
{
public:
    constexpr JsonDocumentOptions() = default;

    bool AllowTrailingCommas() const { return _allow_trailing_commas; }

protected:
    bool _allow_trailing_commas = false;
};

}