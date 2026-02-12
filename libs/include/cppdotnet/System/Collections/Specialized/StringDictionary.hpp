#pragma once

#include <cppdotnet/System/Collections/Generic/Dictionary.hpp>
#include <string>
#include <string_view>


namespace System::Collections::Specialized
{

namespace Types
{

struct StringTransparentHash
{
    using is_transparent = void;

    std::size_t operator()(std::string_view sv) const noexcept
    {
        return std::hash<std::string_view>{}(sv);
    }

    std::size_t operator()(std::string &s) const noexcept
    {
        return std::hash<std::string>{}(s);
    }
};

}

// NOTE: How can I generalize this to be templated like Dictionary
//       but make it all default template parameters AND not be
//       syntactically unwieldy?
class StringDictionary : public Generic::Dictionary<std::string, std::string,
                                                    Types::StringTransparentHash,
                                                    std::equal_to<>>
{
public:
    using Base = Generic::Dictionary<std::string, std::string,
                                     Types::StringTransparentHash,
                                     std::equal_to<>>;

    using Base::Dictionary;
    using Base::operator =;

    StringDictionary(const std::unordered_map<std::string, std::string> &init_value)
        :
        Dictionary( init_value.begin(), init_value.end() )
    {
    }

};

}