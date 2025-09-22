#pragma once

#include <cppdotnet/System/Collections/Generic/Dictionary.hpp>


namespace System::Collections::Specialized
{

namespace Types
{

struct StringDictionaryTransparentHash
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

struct StringDictionaryTransparentEqual
{
    using is_transparent = void;

    bool operator()(std::string_view lhs, std::string_view rhs) const noexcept
    {
        return lhs == rhs;
    }

    bool operator()(const std::string& lhs, const std::string& rhs) const noexcept
    {
        return lhs == rhs;
    }

    bool operator()(std::string_view lhs, const std::string& rhs) const noexcept
    {
        return lhs == rhs;
    }

    bool operator()(const std::string& lhs, std::string_view rhs) const noexcept
    {
        return lhs == rhs;
    }
};

}

// NOTE: How can I generalize this to be templated like Dictionary
//       but make it all default template parameters AND not be
//       syntactically unwieldy?
class StringDictionary : public Generic::Dictionary<std::string, std::string,
                                                    Types::StringDictionaryTransparentHash,
                                                    Types::StringDictionaryTransparentEqual>
{
public:
    using Base = Generic::Dictionary<std::string, std::string,
                                     Types::StringDictionaryTransparentHash,
                                     Types::StringDictionaryTransparentEqual>;

    using Base::Dictionary;
    using Base::operator =;

    void Add(std::string_view key, std::string_view value)
    {
        if ( ContainsKey( key ) )
            ThrowWithTarget( ArgumentException( std::format("Key '{}' is already in the Dictionary", key), "key" ) );

        m_data[ std::string(key) ] = value;
        
        POSTCONDITION( ContainsKey(key) );
    }

    bool Remove(std::string_view key)
    {
        return m_data.erase( std::string(key) ); // TODO: FIXME in C++23
    }

    mapped_type &operator[](std::string_view key)
    {
        return m_data[ std::string(key) ];
    }
};

}