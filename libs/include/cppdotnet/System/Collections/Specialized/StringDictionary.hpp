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

    // We implement this here if it is not already available in the base class
#ifndef __cpp_lib_generic_unordered_lookup
    constexpr auto ContainsKey(std::string_view key) const
    {
        return m_data.contains( key );
    }
#endif

    void Add(std::string_view key, std::string_view value)
    {
        // If there is no heterogenous lookup available, then the non-heterogenous function
        // should be automatically used and a std::string() constructed from this std::string_view.
        if ( ContainsKey(key) )
            ThrowWithTarget( ArgumentException( std::format("Key '{}' is already in the Dictionary", key), "key" ) );

        (*this)[ key ] = value; // call this class' operator [] if we don't have heterogenous insertion, base class otherwise
        
        POSTCONDITION( ContainsKey(key) );
    }

    // We implement this here if it is not already available in the base class
#ifndef __cpp_lib_associative_heterogeneous_erasure
    bool Remove(std::string_view key)
    {
        return Base::Remove( std::string(key) );
    }
#endif

    // We implement this here if it is not already available in the base class
#ifndef __cpp_lib_associative_heterogeneous_insertion
    mapped_type &operator[](std::string_view key)
    {
        return m_data[ std::string(key) ];
    }
#endif

    // We implement this here if it is not already available in the base class
#ifndef __cpp_lib_generic_unordered_lookup
    constexpr bool TryGetValue(std::string_view key, mapped_type &value_out) const
    {
        return TryGetValue( std::string(key), value_out );
    }
#endif

#if !defined(__cpp_lib_generic_unordered_lookup) || !defined(__cpp_lib_associative_heterogeneous_insertion)
    constexpr bool TryAdd(std::string_view key, std::string_view value)
    {
        if ( ContainsKey( key ) )
            return false;
        (*this)[ key ] = value;
        return true;
    }
#endif
    
#ifndef __cpp_lib_associative_heterogeneous_insertion
    const mapped_type &at(std::string_view key) const
    {
        try
        {
            return m_data.at( std::string(key) );
        }
        catch(const std::out_of_range &)
        {
            ThrowWithTarget( Collections::Generic::KeyNotFoundException( std::format("Key '{}' not found in Dictionary", key) ) );
        }
    }

    mapped_type &at(std::string_view key)
    {
        try
        {
            return m_data.at( std::string(key) );
        }
        catch(const std::out_of_range &)
        {
            ThrowWithTarget( Collections::Generic::KeyNotFoundException( std::format("Key '{}' not found in Dictionary", key) ) );
        }
    }
#endif

};

}