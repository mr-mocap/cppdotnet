#pragma once

#include "System/Text/Json/JsonCommentHandling.hpp"
#include "System/Exception.hpp"

#include <string_view>


namespace System::Text::Json
{

class JsonReaderOptions
{
public:
    constexpr JsonReaderOptions() noexcept = default;

    constexpr int MaxDepth() const { return _max_depth; }

    constexpr JsonCommentHandling CommentHandling() const { return _comment_handling; }    
              void                CommentHandling(JsonCommentHandling new_value)
    {
        using namespace std::literals;

        if ( static_cast<int>(new_value) < static_cast<int>(JsonCommentHandling::Disallow) )
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "CommentHandling"sv, "Value is out-of-range"sv } );

        if ( static_cast<int>(new_value) > static_cast<int>(JsonCommentHandling::Allow) )
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "CommentHandling"sv, "Value is out-of-range"sv } );

        _comment_handling = new_value;
    }

    constexpr bool AllowTrailingCommas() const { return _allow_trailing_commas; }
    constexpr void AllowTrailingCommas(bool new_value) { _allow_trailing_commas = new_value; }

    constexpr bool AllowMultipleValues() const { return _allow_multiple_values; }
    constexpr void AllowMultipleValues(bool new_value) { _allow_multiple_values = new_value; }

protected:
    int                 _max_depth = 0;
    JsonCommentHandling _comment_handling = JsonCommentHandling::Disallow;
    bool                _allow_trailing_commas = false;
    bool                _allow_multiple_values = false;
};

}