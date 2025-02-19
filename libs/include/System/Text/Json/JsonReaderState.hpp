#pragma once

#include "System/Text/Json/JsonReaderOptions.hpp"
#include "System/Exception.hpp"


namespace System::Text::Json
{

class JsonReaderState
{
public:
    constexpr JsonReaderState() = default;
    constexpr JsonReaderState(const JsonReaderOptions &options)
        :
        _options{ options }
    {
        using namespace std::literals;

        if (options.MaxDepth() < 0)
            ThrowWithTarget( System::ArgumentException{ "The maximum depth is < 0"sv, "options.MaxDepth"sv } );
    }

    constexpr const JsonReaderOptions &Options() const { return _options; }
          
protected:
    JsonReaderOptions _options;
};

}