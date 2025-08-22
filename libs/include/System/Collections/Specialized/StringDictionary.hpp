#include "System/Collections/Generic/Dictionary.hpp"


namespace System::Collections::Specialized
{

// NOTE: How can I generalize this to be templated like Dictionary
//       but make it all default template parameters AND not be
//       syntactically unwieldy?
class StringDictionary : public Generic::Dictionary<std::string, std::string>
{
public:
    using Base = Generic::Dictionary<std::string, std::string>;

    using Generic::Dictionary<std::string, std::string>::Dictionary;

    constexpr void Add(std::string_view key, std::string_view value) { Base::Add( std::string{key}, std::string{value} ); }
};

}