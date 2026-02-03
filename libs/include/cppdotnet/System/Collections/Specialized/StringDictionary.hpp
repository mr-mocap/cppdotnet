#pragma once

#include <cppdotnet/System/Collections/Generic/Dictionary.hpp>


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
                                                    std::equal_to<void>>
{
public:
    using Base = Generic::Dictionary<std::string, std::string,
                                     Types::StringTransparentHash,
                                     std::equal_to<void>>;

    using Base::Dictionary;
    using Base::operator =;

    StringDictionary(const std::unordered_map<std::string, std::string> &init_value)
        :
        Dictionary( init_value.begin(), init_value.end() )
    {
    }

    void Add(std::string_view key, std::string_view value)
    {
        if ( ContainsKey( key ) )
            ThrowWithTarget( ArgumentException( std::format("Key '{}' is already in the Dictionary", key), "key" ) );

        m_data[ std::string(key) ] = value;
        
        POSTCONDITION( ContainsKey(key) );
    }

    bool Remove(std::string_view key)
    {
#ifdef __cpp_lib_associative_heterogeneous_erasure
        return m_data.erase( key );
#else
        return m_data.erase( std::string(key) );
#endif
    }

    mapped_type &operator[](std::string_view key)
    {
#ifdef __cpp_lib_associative_heterogeneous_insertion
        return m_data[ key ];
#else
        return m_data[ std::string(key) ];
#endif
    }
};

}